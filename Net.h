#ifndef KHAKI_NET_H
#define KHAKI_NET_H

#include "Buffer.h"
#include "Log.h"

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
	class Connector;

	const unsigned int MAX_READ_BUFFER_SIZE = 20480;
	typedef std::weak_ptr<TcpClient> TcpWeakPtr;
	typedef std::shared_ptr<TcpClient> TcpClientPtr;
	typedef std::shared_ptr<Connector> TcpConnectorPtr;
	typedef std::function<void(const TcpClientPtr& con)> Callback;
	typedef std::shared_ptr<TimeWheel> TimeWheelPtr;
	typedef std::function<void(Buffer& buf)> CallbackBuffer;
	typedef std::function<void(const TcpConnectorPtr& con)> CallbackConnector;

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

		void handleRead(const TcpClientPtr& con);
		void handleWrite(const TcpClientPtr& con);

		void setReadCallback(const Callback& cb) { readcb_ = cb; }
		void setWriteCallback(const Callback& cb) { writecb_ = cb; }
		void setCloseCallback(const Callback& cb) { closecb_ = cb; }

		void send(const char* buf, int len);
		void send(Buffer& buf);
		void sendInLoop(Buffer& buf);
		Buffer getBuf() { Buffer tmp(readBuf_); readBuf_.clear(); return tmp; }
		Buffer& getReadBuf() { return readBuf_; }
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
		Callback readcb_, writecb_, closecb_;

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
		void setReadCallback(const Callback& cb) { readcb_ = cb; }
		void setWriteCallback(const Callback& cb) { writecb_ = cb; }
		void setConnectionCallback(const Callback& cb) { newcb_ = cb; }
		void setConnCloseCallback(const Callback& cb) { closecb_ = cb; }

		void send(char* buf);

		int getOnlineNum();
		void addClient(TcpClientPtr& sp);
		void removeClient(const TcpClientPtr& sp);
		void delClient(int fd);
	private:
		void newConnect( int fd, IpAddr& addr );
		void handleAccept();

		EventLoop* loop_;
		Channel* listen_;
		IpAddr addr_;
		Callback readcb_, writecb_, newcb_, closecb_;
		std::mutex mtx_;
		std::map<int, std::weak_ptr<TcpClient>> sSessionList; 
	};

	////////////////////////////////////
	class Connector : public std::enable_shared_from_this<Connector> {
	public:
		enum {
			E_CONNECT_STATUS_CLOSE 	 = 0,
			E_CONNECT_STATUS_CONN 	 = 1,
			E_CONNECT_STATUS_RUNNING = 2,
		};

		Connector(EventLoop* loop, std::string host, uint16_t port);
		~Connector();
		bool connectServer();
		bool retryConnect();
		void setConnectCallback(const CallbackConnector& cb) { newcb_ = cb; }
		void setReadCallback(const CallbackConnector& cb) { readcb_ = cb; }
		void setWriteCallback(const CallbackConnector& cb) { writecb_ = cb; }
		void setCloseCallback(const CallbackConnector& cb) { closecb_ = cb; }
		void send(const char* buf, int len);

		void closeFd(int fd) { close(sockFd_); status_ = E_CONNECT_STATUS_CLOSE;}
		void closeConnect();
		int getFd() { return sockFd_; }
		int getStatus() { return status_; }
		Buffer& getReadBuf() { return readBuf_; }
	private:
		void handleRead(const TcpConnectorPtr& con);
		void handleWrite(const TcpConnectorPtr& con);
		bool checkConnectStatus(const TcpConnectorPtr& con);

		size_t directWrite(Buffer& buffer);
		void send(Buffer& buf);
		void sendInLoop(Buffer& buf);
	private:
		EventLoop* loop_;
		IpAddr addr_;
		int sockFd_;
		int status_;
		Channel* channel_;
		Buffer readBuf_, writeBuf_;
		CallbackConnector newcb_, readcb_, writecb_, closecb_; 
	};

	////////////////////////////////////
	class EventLoopThread;
	class TcpThreadServer : public TcpServer {
	public:
		typedef std::shared_ptr<EventLoopThread> EventLoopThreadPtr;
		
		TcpThreadServer( EventLoop* loop, std::string host, int port, int threadNum = 0 );

		~TcpThreadServer();
		virtual EventLoop* getEventLoop();

	private:
		int index_;
		int threadNum_;
		int threadSize_;
		std::vector<EventLoopThreadPtr> vThreadLoop_;
	};
}

#endif