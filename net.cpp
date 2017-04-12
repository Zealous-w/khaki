#include "net.h"
#include "time_wheel.h"
#include "log.h"

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

	TcpClient::TcpClient( EventLoop* loop ) :
		loop_(loop), 
		channel_(NULL)
	{

	}

	TcpClient::~TcpClient()
	{
		klog_info("~TcpClient");
		delete channel_;
	}

	void TcpClient::handleRead(const TcpClientPtr& con)
	{
		klog_info("TcpClient::handleRead");
		memset(buf, 0, 1024);
		int n = read(channel_->fd(), buf, 1024);
		klog_info("TcpClient::readcb_");

		if ( n == 0 ) { closeClient(); return; }
		if ( readcb_ ) readcb_(con);
	}

	void TcpClient::handleWrite(const TcpClientPtr& con)
	{

	}

	int TcpClient::getFd()
	{
		return channel_->fd();
	}

	void TcpClient::send(char* buf)
	{
		write(channel_->fd(), buf, strlen(buf));
	}

	void TcpClient::registerChannel( int fd )
	{
		channel_ = new Channel(loop_, fd, kReadEv);
		TcpClientPtr conPtr = shared_from_this();
		conPtr->channel_->OnRead([=](){conPtr->handleRead(conPtr);});
		conPtr->channel_->OnWrite([=](){conPtr->handleWrite(conPtr);});
	}

	void TcpClient::closeClient()
	{
		readcb_ = NULL;
		writecb_ = NULL;

		// TODO 
		Channel* ch = channel_;
	    channel_ = NULL;
		delete ch;
	}

	//////////////////////////////////////
	TcpServer::TcpServer( EventLoop* loop, std::string host, int port ):
		loop_(loop), 
		listen_(NULL), 
		addr_(host, port), 
		time_wheel(new TimeWheel(1 << 6))
	{
		time_wheel_ = new Channel(loop, time_wheel->getTimeFd(), kReadEv);
		time_wheel_->OnRead([this]{ handleTimeWheel(); });
	}

	TcpServer::~TcpServer()
	{
		delete listen_;
		delete time_wheel;
	}

	void TcpServer::start()
	{
		int fd_ = socket(AF_INET, SOCK_STREAM, 0);
		int ret = bind(fd_, (struct sockaddr*)&addr_.getAddr(), sizeof(struct sockaddr));
		if (ret == -1)
		{
			klog_info("TcpServer Bind Error");
			close(fd_);
			return;
		}

		if (listen(fd_, 5) == -1 )
		{
			close(fd_);
			return;
		}

		listen_ = new Channel(loop_, fd_, kReadEv);
		listen_->OnRead([this]{ handleAccept(); });

		klog_info("TcpServer Listen %s:%d", addr_.getIp().c_str(), addr_.getPort());
	}

	void TcpServer::send(char* buf)
	{

	}

	void TcpServer::newConnect( int fd, IpAddr& addr )
	{
		TcpClientPtr conPtr( new TcpClient(loop_));
		conPtr->setReadCallback(readcb_);
		conPtr->registerChannel(fd);

		time_wheel->addTcpClient(conPtr);
	}

	void TcpServer::handleAccept()
	{
		struct sockaddr_in caddr;
		socklen_t csize = sizeof(struct sockaddr);

		int connfd = accept(listen_->fd(), (struct sockaddr*)&caddr, &csize);
		if ( connfd >= 0 )
		{
			IpAddr cAddr(caddr);
			newConnect( connfd, cAddr );
			klog_info("handleAccept");
		}
	}

	void TcpServer::handleTimeWheel()
	{
		time_wheel->handlerRead();
	}
}