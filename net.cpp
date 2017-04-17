#include "net.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "channel.h"
#include "time_wheel.h"

namespace khaki {

	IpAddr::IpAddr(struct sockaddr_in& addr)
	{
		addr_ = addr;
	}

	IpAddr::IpAddr(std::string& host, int port)
	{
		memset(&addr_, 0, sizeof(addr_));
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(port);
		addr_.sin_addr.s_addr = inet_addr(host.c_str());
	}

	IpAddr::~IpAddr(){}

	std::string IpAddr::getIp() const
	{
		char buf[32]={0};
		inet_ntop(AF_INET, &addr_.sin_addr, buf, static_cast<socklen_t>(strlen(buf)));
		return std::string(buf);
	}

	int IpAddr::getPort() const
	{
		return ntohs(addr_.sin_port);
	}

	struct sockaddr_in& IpAddr::getAddr()
	{ 
		return addr_; 
	}

	//////////////////////////////////////

	TcpClient::TcpClient( EventLoop* loop, TcpServer* server ) :
		loop_(loop), server_(server)
	{
		//klog_info("TcpClient");
	}

	TcpClient::~TcpClient()
	{
		//klog_info("~TcpClient");
	}

	void TcpClient::handleRead(const TcpClientPtr& con)
	{
		char buf[20480] = {0};
		int n = 0;
		while ( true )
		{
			n = read(channel_->fd(), buf, 20480 );
			if ( n < 0 && errno == EINTR )
			{
				//klog_info("read continue by EAGAIN"); continue;
			} else if ( n < 0 && ( errno == EAGAIN || errno == EWOULDBLOCK ) )
			{
				//klog_info("TcpClient::handleRead size : %d, buff : %s", n, buf_.show().c_str());
				if ( readcb_ ) readcb_(con); break;
			} else if ( channel_->fd() == -1 || n == 0 || n == -1 )	
			{
				//klog_info("read close by reset");
				closeClient(con); break;
			} else 
			{
				readBuf_.append(buf, n);
				last_read_time_ = util::getTime();
				updateTimeWheel();
			}
		}
		//klog_info("********read end return");
	}

	void TcpClient::handleWrite(const TcpClientPtr& con)
	{
		int size = directWrite(writeBuf_.begin(), writeBuf_.size());
		writeBuf_.addBegin(size);
		klog_info("****** trigger EPOLL_OUT");
	}

	int TcpClient::directWrite(const char* buf, int len)
	{
		int writeSize = len;
		int sendSize = 0;
		int ret = 0;
		while ( writeSize > sendSize )
		{
			ret = write(channel_->fd(), buf, len - sendSize );
			if (ret > 0) {
				sendSize += ret;
				
				continue;
			} else if (ret == -1 && errno == EINTR) {
				continue;
			} else if (ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
				break;
			} else {
				klog_info("write error client closed");
				break;
			}
		}
	}

	int TcpClient::getFd()
	{
		return channel_->fd();
	}

	int TcpClient::getLastTime()
	{
		return last_read_time_;
	}

	void TcpClient::updateTimeWheel()
	{
		TcpClientPtr conPtr = shared_from_this();
		loop_->getTimeWheelPtr()->addTcpClient(conPtr);
	}

	void TcpClient::send(char* buff, int len)
	{
		write(channel_->fd(), buff, len);
	}

	void TcpClient::send(Buffer& buf)
	{
		//write(channel_->fd(), buf.begin(), buf.size());
		if ( buf.size() )
		{
			int size = directWrite(buf.begin(), buf.size());
			buf.addBegin(size);
		}
		if ( buf.size() )
		{
			writeBuf_.append(buf.begin(), buf.size());
			if (!channel_->writeStatus()) channel_->enableWrite(true);
		}
	}

	void TcpClient::registerChannel( int fd )
	{
		channel_ = std::shared_ptr<Channel>(new Channel(loop_, fd, kReadEv));

		TcpClientPtr conPtr = shared_from_this();
		conPtr->channel_->OnRead([=](){conPtr->handleRead(conPtr);});
		conPtr->channel_->OnWrite([=](){conPtr->handleWrite(conPtr);});

		updateTimeWheel();
	}

	void TcpClient::closeClient(const TcpClientPtr& con)
	{
		if (readcb_ && readBuf_.size()) {
        	readcb_(con);
    	}
		readcb_ = NULL;
		writecb_ = NULL;

		channel_.reset();
	}

	//////////////////////////////////////
	TcpServer::TcpServer( EventLoop* loop, std::string host, int port ):
		loop_(loop), 
		listen_(NULL), 
		addr_(host, port)
	{
	}

	TcpServer::~TcpServer()
	{
		delete listen_;
	}

	void TcpServer::start()
	{
		int fd_ = socket(AF_INET, SOCK_STREAM, 0);
		if ( util::setReuseAddr(fd_) == -1 )
		{
			klog_info("TcpServer Sockopt Error");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		util::setNonBlock(fd_);

		int ret = bind(fd_, (struct sockaddr*)&addr_.getAddr(), sizeof(struct sockaddr));
		if (ret == -1)
		{
			klog_info("TcpServer Bind Error, please wait a minutes");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		if (listen(fd_, 20) == -1 )
		{
			klog_info("TcpServer Listen Error");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		listen_ = new Channel(loop_, fd_, kReadEv);
		listen_->OnRead([this]{ handleAccept(); });

		klog_info("TcpServer Listen %s:%d", addr_.getIp().c_str(), addr_.getPort());
	}

	void TcpServer::send(char* buf)
	{

	}

	int TcpServer::getOnlineNum()
	{
		int count = 0;

		mtx_.lock();
		count = sSessionList.size();
		mtx_.unlock();

		return count;
	}

	void TcpServer::addClient(std::shared_ptr<TcpClient>& sp)
	{
		mtx_.lock();
		sSessionList.insert( std::make_pair(sp->getFd(), std::weak_ptr<TcpClient>(sp)) );
		mtx_.unlock();
	}

	void TcpServer::delClient(int fd)
	{
		mtx_.lock();
		auto sc = sSessionList.find(fd);
		if ( sc != sSessionList.end() ) sSessionList.erase(fd);
		mtx_.unlock();
	}

	void TcpServer::newConnect( int fd, IpAddr& addr )
	{
		EventLoop* loop_c = getEventLoop();
		util::setNonBlock(fd);
		TcpClientPtr conPtr( new TcpClient(loop_c, this));
		conPtr->setReadCallback(readcb_);
		conPtr->registerChannel(fd);
	}

	void TcpServer::handleAccept()
	{
		struct sockaddr_in caddr;
		socklen_t csize = sizeof(struct sockaddr);
		int connfd = -1;
		while ( ( connfd = accept(listen_->fd(), (struct sockaddr*)&caddr, &csize) ) != -1 ) 
		{
			IpAddr cAddr(caddr);
			//klog_info("Accept a new connection %d", connfd);
			newConnect( connfd, cAddr );
		}
	}

	/////////////////////////////////////////
	TcpThreadServer::TcpThreadServer( EventLoop* loop, std::string host, int port ) :
			index_(0),
			TcpServer(loop, host, port), 
			threadNum(std::thread::hardware_concurrency())
		{
			klog_info("threadNum : %d", threadNum);
			for ( int i = 0; i < threadNum; i++ ) {
				vThreadLoop_.push_back(EventLoopThreadPtr(new EventLoopThread()));
			}

			for ( auto v : vThreadLoop_ ) {
				v->startLoop();
			}

			threadSize = vThreadLoop_.size();
		}

		TcpThreadServer::~TcpThreadServer()
		{
		}

		EventLoop* TcpThreadServer::getEventLoop() 
		{
			index_++;
			if ( index_  >= threadSize ) index_ = 0;
			//klog_info("getEventLoop() index_ : %d Sum : %d", index_, threadSize);
			return vThreadLoop_[index_]->getLoop();
		}  
}