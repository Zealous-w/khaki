#ifndef KHAKI_POLL_H
#define KHAKI_POLL_H
#include "EventLoop.h"
#include "Util.h"

#include <iostream>
#include <sys/epoll.h>
#include <poll.h>
#include <functional>
#include <set>
#include <unistd.h>

namespace khaki{
	const int kMaxEvents = 1024;
    const int kReadEv    = POLLIN;
    const int kWriteEv   = POLLOUT;
    
	class Channel;
    class PollBase : private noncopyable {
    public:
        PollBase(){}
        virtual ~PollBase(){}

        virtual void addChannel( Channel* ch ) = 0;
    	virtual void updateChannel( Channel* ch ) = 0;
    	virtual void removeChannel( Channel* ch ) = 0;
    };


    class PollEpoll : public PollBase {
    public:
    	typedef std::set<Channel*> ChannelSet;

    	PollEpoll();
    	~PollEpoll();

    	void poll(int timeout=500);

    	void addChannel( Channel* ch ) ;
    	void updateChannel( Channel* ch ) ;
    	void removeChannel( Channel* ch ) ;
    private:
    	int evId_;
    	ChannelSet sChannel_;
    	struct epoll_event activeEv_[kMaxEvents];
    };
}

#endif //KHAKI_POLL_H
