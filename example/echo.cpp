#include "../khaki.h"
#include <map>

class EchoServer {
public:
	EchoServer(khaki::EventLoop* loop, std::string host, int port, int threadNum) : 
		server_(loop, host, port, threadNum) {
		server_.setReadCallback(std::bind(&EchoServer::OnMessage, 
							this, std::placeholders::_1));
		server_.setConnectionCallback(std::bind(&EchoServer::OnConnection, 
							this, std::placeholders::_1));
		server_.setConnCloseCallback(std::bind(&EchoServer::OnConnClose, 
							this, std::placeholders::_1));
	}

	void start() {
		server_.start();
	}

	void OnConnection(const khaki::TcpClientPtr& con) {
		std::cout << "OnConnection online num : " << server_.getOnlineNum() << std::endl;
		std::unique_lock<std::mutex> lck(mtx_);
		sessionLists_.insert(std::make_pair(con->getFd(), khaki::TcpWeakPtr(con)));
	}

	void OnConnClose(const khaki::TcpClientPtr& con) {
		std::cout << "OnConnClose online num : " << server_.getOnlineNum() << std::endl;
		std::unique_lock<std::mutex> lck(mtx_);
		sessionLists_.erase(con->getFd());
	}

	void OnMessage(const khaki::TcpClientPtr& con) {
		khaki::Buffer tmp(con->getBuf());
		broadcastMsg(tmp);
	}

	void broadcastMsg(khaki::Buffer& msg) {
		std::unique_lock<std::mutex> lck(mtx_);
		for (auto s : sessionLists_) {
			khaki::Buffer tmp(msg);
			khaki::TcpClientPtr c = s.second.lock();
			if(c) { 
				c->send(tmp);
			}
		}
	}
private:
	khaki::TcpThreadServer server_;
	std::mutex mtx_;
	std::unordered_map<int, khaki::TcpWeakPtr> sessionLists_;
};

int main( int argc, char* argv[] )
{
	khaki::EventLoop loop;
	khaki::InitLog(khaki::logger, "./echo.log", log4cpp::Priority::DEBUG);
	
	EchoServer echo(&loop, "127.0.0.1", 9527, 4);
	echo.start();

	loop.loop();
	return 0;
}