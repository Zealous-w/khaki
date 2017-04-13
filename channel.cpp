#include "channel.h"
#include "log.h"

namespace khaki {
	Channel::Channel(EventLoop* loop, int fd, int event):
    	loop_(loop), fd_(fd), events(event)
	{
		klog_info("Channel : %d", fd_);
	    loop_->getPoll()->addChannel(this);
	}

	Channel::~Channel()
	{
		klog_info("~Channel : %d", fd_);
	    loop_->getPoll()->removeChannel(this);
	    close(fd_);
	}

	EventLoop* Channel::getEventLoop() { return loop_; }
	int Channel::getEvents() { return events; }
	int Channel::fd() { return fd_; }

	void Channel::OnRead(const FunctionCallback_& readcb) { readcb_ = readcb; } 
	void Channel::OnWrite(const FunctionCallback_& writecb) { writecb_ = writecb; }

	void Channel::handleRead() { readcb_(); }
	void Channel::handleWrite() { writecb_(); }
}
