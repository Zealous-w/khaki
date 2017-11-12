#include "Net.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "Channel.h"
#include "TimeWheel.h"
#include "Util.h"

namespace khaki {

	IpAddr::IpAddr(const struct sockaddr_in& addr):addr_(addr)
	{
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
		uint32_t uip = addr_.sin_addr.s_addr;
		return util::string_format("%d.%d.%d.%d",
			(uip >> 0)&0xff,
			(uip >> 8)&0xff,
			(uip >> 16)&0xff,
			(uip >> 24)&0xff);
	}

	int IpAddr::getPort() const
	{
		return ntohs(addr_.sin_port);
	}

	struct sockaddr_in& IpAddr::getAddr()
	{ 
		return addr_; 
	}

	uint64_t IpAddr::toIpPort() const
	{
		uint32_t port = ntohs(addr_.sin_port);
		uint32_t ip = addr_.sin_addr.s_addr;
		return uint64_t(ip) << 32 | ((uint64_t(port) << 16) & 0xFF00);
	}

	//////////////////////////////////////
	TcpClient::TcpClient( EventLoop* loop, TcpServer* server, IpAddr& addr, uint32_t uniqueId ) :
		loop_(loop), server_(server), addr_(addr), uniqueId_(uniqueId)
	{
	}

	TcpClient::~TcpClient()
	{
	}

	void TcpClient::handleRead(const TcpClientPtr& con)
	{
		char buf[MAX_READ_BUFFER_SIZE] = {0};
		int n = 0;
		while ( true )
		{
			n = read(channel_->fd(), buf, MAX_READ_BUFFER_SIZE );
			if ( n < 0 && errno == EINTR )
			{
			} else if ( n < 0 && ( errno == EAGAIN || errno == EWOULDBLOCK ) )
			{
				if ( readcb_ ) readcb_(con); break;
			} else if ( channel_->fd() == -1 || n == 0 || n == -1 )	
			{
				closeClient(con); break;
			} else 
			{
				readBuf_.append(buf, n);
				last_read_time_ = util::getTime();
				updateTimeWheel();
			}
		}
	}

	void TcpClient::handleWrite(const TcpClientPtr& con)
	{
		int size = directWrite(writeBuf_.begin(), writeBuf_.size());
		writeBuf_.addBegin(size);
		if (writeBuf_.empty()) {
			if (writecb_) writecb_(con);
			if (channel_->writeStatus()) channel_->enableWrite(false);
		}
	}

	int TcpClient::directWrite(const char* buf, int len)
	{
		int writeSize = len;
		int sendSize = 0;
		int ret = 0;
		while ( writeSize > sendSize )
		{
			ret = write(channel_->fd(), buf + sendSize, len - sendSize );
			if (ret > 0) {
				sendSize += ret;
				continue;
			} else if (ret == -1 && errno == EINTR) {
				continue;
			} else if (ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
				break;
			} else {
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

	void TcpClient::send(const char* buff, int len)
	{
		Buffer buf;
		buf.append(buff, len);
		send(buf);
	}

	void TcpClient::send(Buffer& buf)
	{
		if (loop_->isInLoopThread())
		{
			sendInLoop(buf);
		}
		else
		{
			loop_->executeInLoop(std::bind(&TcpClient::sendInLoop, this, Buffer(buf)));
		}
	}

	void TcpClient::sendInLoop(Buffer& buf)
	{
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
		channel_ = std::shared_ptr<Channel>(new Channel(loop_, fd));

		TcpClientPtr conPtr = shared_from_this();
		conPtr->channel_->OnRead(std::bind(&TcpClient::handleRead, this, conPtr));
		conPtr->channel_->OnWrite(std::bind(&TcpClient::handleWrite, this, conPtr));

		updateTimeWheel();
	}

	void TcpClient::closeClient(const TcpClientPtr& con)
	{
		if (readcb_ && readBuf_.size()) {
        	readcb_(con);
    	}
		if ( closecb_ ) closecb_(con);

		readcb_ = NULL;
		writecb_ = NULL;

		channel_.reset();
	}

	void TcpClient::enableRead() 
	{
		if (channel_) channel_->enableRead(true);
	}

	//////////////////////////////////////
	TcpServer::TcpServer( EventLoop* loop, std::string host, int port ):
		loop_(loop), 
		listen_(NULL), 
		addr_(host, port),
		uniqueId_(0)
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
			log4cppDebug(logger, "TcpServer Sockopt Error");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		util::setNonBlock(fd_);

		int ret = bind(fd_, (struct sockaddr*)&addr_.getAddr(), sizeof(struct sockaddr));
		if (ret == -1)
		{
			log4cppDebug(logger, "TcpServer Bind Error, please wait a minutes");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		if (listen(fd_, SOMAXCONN) == -1 )
		{
			log4cppDebug(logger, "TcpServer Listen Error");
			close(fd_);
			loop_->setStatus(false);
			return;
		}

		listen_ = new Channel(loop_, fd_);
		listen_->OnRead([this]{ handleAccept(); });
		listen_->enableRead(true);
		log4cppDebug(logger, "TcpServer Listen %s:%d", addr_.getIp().c_str(), addr_.getPort());
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

	void TcpServer::addClient(TcpClientPtr& sp)
	{
		mtx_.lock();
		sSessionList.insert( std::make_pair(sp->getFd(), std::weak_ptr<TcpClient>(sp)) );
		mtx_.unlock();
	}

	void TcpServer::removeClient(const TcpClientPtr& sp)
	{
		mtx_.lock();
		auto sc = sSessionList.find(sp->getFd());
		if ( sc != sSessionList.end() ) sSessionList.erase(sp->getFd());
		mtx_.unlock();
		if (closecb_) closecb_(sp);
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
		//util::setNonBlock(fd);
		uniqueId_++;
		TcpClientPtr conPtr(new TcpClient(loop_c, this, addr, uniqueId_));
		{
			conPtr->setReadCallback(readcb_);
			conPtr->setCloseCallback(std::bind(&TcpServer::removeClient, this, std::placeholders::_1));
			conPtr->registerChannel(fd);
			if (newcb_) newcb_(conPtr);
			conPtr->enableRead();
			addClient(conPtr);
		}
	}

	void TcpServer::handleAccept()
	{
		struct sockaddr_in caddr;
		socklen_t csize = sizeof(struct sockaddr);
		int connfd = -1;
		while ( ( connfd = accept4(listen_->fd(), (struct sockaddr*)&caddr, &csize, SOCK_NONBLOCK) ) != -1 ) 
		{
			IpAddr cAddr(caddr);
			newConnect( connfd, cAddr );
		}
	}

	/////////////////////////////////////////
	TcpThreadServer::TcpThreadServer( EventLoop* loop, std::string host, int port, int threadNum ) :
			index_(0),
			TcpServer(loop, host, port), 
			threadNum_(threadNum)
		{
			if (threadNum_ == 0) { threadNum_ = std::thread::hardware_concurrency(); }
			
			for ( int i = 0; i < threadNum; i++ ) {
				vThreadLoop_.push_back(EventLoopThreadPtr(new EventLoopThread()));
			}

			for ( auto v : vThreadLoop_ ) {
				v->startLoop();
			}

			threadSize_ = vThreadLoop_.size();
		}

		TcpThreadServer::~TcpThreadServer()
		{
			for (auto iThread : vThreadLoop_) {
				iThread.reset();
			}
		}

		EventLoop* TcpThreadServer::getEventLoop() 
		{
			index_++;
			if ( index_  >= threadSize_ ) index_ = 0;
			return vThreadLoop_[index_]->getLoop();
		}

		///////////////////////////////////
		Connector::Connector(EventLoop* loop, std::string host, uint16_t port, int timeout):
			loop_(loop), addr_(host, int(port)), channel_(NULL), timeout_(timeout)
		{
			status_ = E_CONNECT_STATUS_CLOSE;
		}

		Connector::~Connector()
		{
			if ( channel_ != NULL ) {delete channel_;}
		}

		bool Connector::connectServer()
		{
			if (status_ == E_CONNECT_STATUS_RUNNING) return false;

			status_ = E_CONNECT_STATUS_CLOSE;

			int sockFd = socket(AF_INET, SOCK_STREAM, 0);
			if ( sockFd < 0 ) {
				log4cppDebug(logger, "socket error, sockFd : %d", sockFd);
				return false;
			}

			util::setNonBlock(sockFd);

			int cRet = connect(sockFd, (struct sockaddr*)&addr_.getAddr(), sizeof(struct sockaddr));
			if ( cRet < 0 && errno != EINPROGRESS ) {
				log4cppDebug(logger, "Connector connect Error, %d, errno : %d", cRet,  errno);
				closeFd(sockFd);
				return false;
			}
			
			TcpConnectorPtr con = shared_from_this();
			channel_ = new Channel(loop_, sockFd);
			channel_->OnRead([=]{ handleRead(con); });
			channel_->OnWrite([=]{ handleWrite(con); });
			channel_->enableWrite(true);
			sockFd_ = sockFd;
			status_ = E_CONNECT_STATUS_CONN;

			loop_->getTimer()->AddTimer(std::bind(&Connector::timeout, this), khaki::util::getTime() + this->timeout_, 0);//timeout
			return true;
		}

		bool Connector::retryConnect()
		{
			closeConnect();
			return connectServer();
		}

		void Connector::closeConnect()
		{
			status_ = E_CONNECT_STATUS_CLOSE;
			if (readcb_ && readBuf_.size()) {
        		readcb_(shared_from_this());
    		}

			delete channel_;
			channel_ = NULL;
		}

		void Connector::timeout() {
			if (status_ == E_CONNECT_STATUS_RUNNING) return;
			closeConnect();
			loop_->stop();
			log4cppDebug(logger, "Connector::timeout");
		}

		void Connector::send(const char* buff, int len)
		{
			Buffer buf;
			buf.append(buff, len);
			send(buf);
		}

		void Connector::send(Buffer& buf)
		{
			if (loop_->isInLoopThread())
			{
				sendInLoop(buf);
			}
			else
			{
				loop_->executeInLoop(std::bind(&Connector::sendInLoop, this, Buffer(buf)));
			}
		}

		void Connector::sendInLoop(Buffer& buf)
		{
			if ( buf.size() )
			{
				directWrite(buf);
			}
			if ( buf.size() )
			{
				writeBuf_.append(buf.begin(), buf.size());
				if (!channel_->writeStatus()) channel_->enableWrite(true);
			}
		}

		size_t Connector::directWrite(Buffer& buffer)
		{
			char* buf = buffer.data();
			int len = buffer.size();
			int writeSize = buffer.size();
			int sendSize = 0;
			int ret = 0;
			while ( writeSize > sendSize )
			{
				ret = write(channel_->fd(), buf + sendSize, len - sendSize );
				if (ret > 0) {
					sendSize += ret;
					continue;
				} else if (ret == -1 && errno == EINTR) {
					continue;
				} else if (ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
					break;
				} else {
					//close
					status_ = E_CONNECT_STATUS_CLOSE;
					break;
				}
			}
			buffer.addBegin(sendSize);
		}

		bool Connector::checkConnectStatus(const TcpConnectorPtr& con) 
		{
			int err = 0;
			socklen_t errlen = sizeof(err);
			if (getsockopt(sockFd_, SOL_SOCKET, SO_ERROR, &err, &errlen) == 0) {
				status_ = E_CONNECT_STATUS_RUNNING;
				channel_->enableWrite(false);
				channel_->enableRead(true);
				if (newcb_) newcb_(con);
				log4cppDebug(logger, "connect success");
				return true;
			} else {
				log4cppDebug(logger, "connect failed");
				return false;
			}
			
			return false;
		}

		void Connector::handleRead(const TcpConnectorPtr& con)
		{
			if ( status_ != E_CONNECT_STATUS_RUNNING ) {
				return;
			}
			char buf[MAX_READ_BUFFER_SIZE] = {0};
			int n = 0;
			while ( true )
			{
				n = read(channel_->fd(), buf, MAX_READ_BUFFER_SIZE );
				if ( n < 0 && errno == EINTR )
				{
				} else if ( n < 0 && ( errno == EAGAIN || errno == EWOULDBLOCK ) )
				{
					if ( readcb_ ) readcb_(con); break;
				} else if ( channel_->fd() == -1 || n == 0 || n == -1 )	
				{
					closeFd(sockFd_); break;
				} else 
				{
					readBuf_.append(buf, n);
				}
			}
		}

		void Connector::handleWrite(const TcpConnectorPtr& con)
		{
			if ( status_ == E_CONNECT_STATUS_CONN ) {
				checkConnectStatus(con);
				return;
			}
			directWrite(writeBuf_);
			if (writeBuf_.empty()) {
				if (writecb_) writecb_(con);
				if (channel_->writeStatus()) channel_->enableWrite(false);
			}
		}
}