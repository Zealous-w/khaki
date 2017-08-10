#include "Channel.h"
#include "EventLoop.h"

namespace khaki {
	Channel::Channel(EventLoop* loop, int fd):
    		loop_(loop), fd_(fd), events_(EPOLLET), readcb_(NULL), writecb_(NULL)
	{
	    loop_->getPoll()->addChannel(this);
	}

	Channel::~Channel()
	{
	    loop_->getPoll()->removeChannel(this);
	    close(fd_);
		fd_ = -1;
	}

	EventLoop* Channel::getEventLoop() { return loop_; }
	int Channel::getEvents() { return events_; }
	int Channel::fd() { return fd_; }

	bool Channel::readStatus()
	{
		return events_ & kReadEv;
	}

    bool Channel::writeStatus()
	{
		return events_ & kWriteEv;
	}

	void Channel::enableRead(bool enable)
	{
		if (enable) 
		{
			events_ |= kReadEv;
		} else 
		{
			events_ &= ~kReadEv;
		}
		loop_->getPoll()->updateChannel(this);
	}

    void Channel::enableWrite(bool enable)
	{
		if (enable) 
		{
			events_ |= kWriteEv;
		} else 
		{
			events_ &= ~kWriteEv;
		}
		loop_->getPoll()->updateChannel(this);
	}

	void Channel::OnRead(const FunctionCallback_& readcb) { readcb_ = readcb; } 
	void Channel::OnWrite(const FunctionCallback_& writecb) { writecb_ = writecb; }

	void Channel::handleRead() { if ( readcb_ ) readcb_(); }
	void Channel::handleWrite() { if ( writecb_ ) writecb_(); }
}
