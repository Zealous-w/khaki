#ifndef KHAKI_NET_H
#define KHAKI_NET_H

#include "EventLoop.h"
#include "channel.h"
#include "log.h"

#include <arpa/inet.h>
#include <string.h>
#include <memory>

namespace khaki {

	class TcpClient;
	class TimeWheel;
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
	class TcpClient : public std::enable_shared_from_this<TcpClient> {
	public:
		TcpClient( EventLoop* loop );
		~TcpClient();

		void handleRead(const TcpClientPtr& con) ;
		void handleWrite(const TcpClientPtr& con) ;

		void setReadCallback(const Callback& cb) { readcb_ = cb; }
		void setWriteCallback(const Callback& cb) { writecb_ = cb; }

		void send(char* buf);
		char* getBuf() { return buf; }
		void registerChannel(int fd);
		void closeClient();
		int getFd();
	private:
		EventLoop* loop_;
		Channel* channel_;
		Callback readcb_, writecb_;
		char buf[1024];
		
	};

	////////////////////////////////////
	class TcpServer {
	public:
		
		TcpServer( EventLoop* loop, std::string host, int port );
		~TcpServer();

		void start();

		EventLoop* getEventLoop() { return loop_; }  
		void handlerRead(const Callback& cb) { readcb_ = cb; }
		void handlerWrite(const Callback& cb) { writecb_ = cb; }

		void send(char* buf);
	private:
		EventLoop* loop_;
		Channel* listen_;
		Channel* time_wheel_;

		IpAddr addr_;
		Callback readcb_, writecb_, newcb_;
		TimeWheel* time_wheel;
		void newConnect( int fd, IpAddr& addr );
		void handleAccept();
		void handleTimeWheel();
	};
}

#endif