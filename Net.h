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

		void handleRead(const TcpClientPtr& con);
		void handleWrite(const TcpClientPtr& con);

		void setReadCallback(const Callback& cb) { readcb_ = cb; }
		void setWriteCallback(const Callback& cb) { writecb_ = cb; }
		void setCloseCallback(const Callback& cb) { closecb_ = cb; }

		void send(char* buf, int len);
		void send(Buffer& buf);
		void sendInLoop(Buffer& buf);
		Buffer getBuf() { Buffer tmp(readBuf_); readBuf_.clear(); return tmp; }
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