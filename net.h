#ifndef KHAKI_NET_H
#define KHAKI_NET_H

#include "buffer.h"
#include "log.h"

#include <arpa/inet.h>
#include <string.h>
#include <memory>
#include <mutex>
#include <thread>

namespace khaki {
	class EventLoop;
	class TcpClient;
	class TimeWheel;
	class Channel;

	typedef std::weak_ptr<TcpClient> TcpWeakPtr;
	typedef std::shared_ptr<TcpClient> TcpClientPtr;
	typedef std::function<void(const TcpClientPtr& con)> Callback;

	typedef std::shared_ptr<TimeWheel> TimeWheelPtr;

	class IpAddr {
	public:
		IpAddr(struct sockaddr_in& addr);
		IpAddr(std::string& host, int port);

		~IpAddr();

		std::string getIp() const;
		int getPort() const;
		struct sockaddr_in& getAddr();
	private:
		struct sockaddr_in addr_;
	};

	////////////////////////////////////
	class TcpServer;
	class TcpClient : public std::enable_shared_from_this<TcpClient> {
	public:
		TcpClient( EventLoop* loop, TcpServer* server );
		~TcpClient();

		void handleRead(const TcpClientPtr& con) ;
		void handleWrite(const TcpClientPtr& con) ;

		void setReadCallback(const Callback& cb) { readcb_ = cb; }
		void setWriteCallback(const Callback& cb) { writecb_ = cb; }

		void send(char* buf, int len);
		void send(Buffer& buf);
		Buffer& getBuf() { return readBuf_; }
		void registerChannel(int fd);
		void closeClient(const TcpClientPtr& con);
		int getFd();
		int getLastTime();
		void updateTimeWheel();

	private:
		int directWrite(const char* buf, int len);
		EventLoop* loop_;
		TcpServer* server_;
		std::shared_ptr<Channel> channel_;
		Callback readcb_, writecb_;

		int last_read_time_;

		Buffer readBuf_, writeBuf_;
	};

	////////////////////////////////////
	class TcpServer : public noncopyable {
	public:
		
		TcpServer( EventLoop* loop, std::string host, int port );
		virtual ~TcpServer();

		void start();

		virtual EventLoop* getEventLoop() { return loop_; }  
		void handlerRead(const Callback& cb) { readcb_ = cb; }
		void handlerWrite(const Callback& cb) { writecb_ = cb; }

		void send(char* buf);

		int getOnlineNum();
		void addClient(std::shared_ptr<TcpClient>& sp);
		void delClient(int fd);
	private:
		void newConnect( int fd, IpAddr& addr );
		void handleAccept();

		EventLoop* loop_;
		Channel* listen_;
		IpAddr addr_;
		Callback readcb_, writecb_, newcb_;
		std::mutex mtx_;
		std::map<int, std::weak_ptr<TcpClient>> sSessionList; 
	};

	////////////////////////////////////
	class EventLoopThread;
	class TcpThreadServer : public TcpServer {
	public:
		typedef std::shared_ptr<EventLoopThread> EventLoopThreadPtr;
		
		TcpThreadServer( EventLoop* loop, std::string host, int port );

		~TcpThreadServer();
		virtual EventLoop* getEventLoop();

	private:
		int index_;
		int threadNum;
		int threadSize;
		std::vector<EventLoopThreadPtr> vThreadLoop_;
	};
}

#endif