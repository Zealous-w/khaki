#include "PollEpoll.h"
#include "Channel.h"

namespace khaki {

	PollEpoll::PollEpoll()
	{
		evId_ = epoll_create1(EPOLL_CLOEXEC);
	}

	PollEpoll::~PollEpoll()
	{
		::close(evId_);
	}

	void PollEpoll::addChannel(Channel* ch) 
	{
		struct epoll_event ev;
		ev.events = ch->getEvents();
		ev.data.ptr = ch;
		int ret = epoll_ctl( evId_, EPOLL_CTL_ADD, ch->fd(), &ev );
		sChannel_.insert(ch);
	}

	void PollEpoll::updateChannel(Channel* ch) 
	{
		struct epoll_event ev;
		ev.events = ch->getEvents();
		ev.data.ptr = ch;
		int ret = epoll_ctl( evId_, EPOLL_CTL_MOD, ch->fd(), &ev );
	}

	void PollEpoll::removeChannel(Channel* ch) 
	{
		struct epoll_event ev;
		ev.events = ch->getEvents();
		ev.data.ptr = ch;
		int ret = epoll_ctl( evId_, EPOLL_CTL_DEL, ch->fd(), &ev );
		sChannel_.erase(ch);
	}

	void PollEpoll::poll()
	{
		int live = epoll_wait(evId_, activeEv_, kMaxEvents, 10000);

		for ( int i = 0; i < live; i++ )
		{
			int events = activeEv_[i].events;
			Channel* ch = (Channel*)activeEv_[i].data.ptr;
			if (ch)
			{
				if ( events & (POLLERR | kReadEv) )
				{
					ch->handleRead();
				}else if ( events & kWriteEv )
				{
					ch->handleWrite();
				}
			}
		}
	}
}