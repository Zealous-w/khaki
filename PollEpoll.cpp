#include "PollEpoll.h"
#include "Channel.h"
#include "Log.h"

namespace khaki {

	PollEpoll::PollEpoll():activeEv_(kMaxEvents)
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

	void PollEpoll::poll(int timeout)
	{
		int eventsRet = ::epoll_wait(evId_, &*activeEv_.begin(), static_cast<int>(activeEv_.size()), timeout);
		
		if (eventsRet > 0) 
		{
			for ( int i = 0; i < eventsRet; i++ )
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
			if (size_t(eventsRet) == activeEv_.size())
			{
				activeEv_.resize(activeEv_.size() * 2);
			}
		} else if (eventsRet < 0) {
			if (errno == EBADF) {
				log4cppError(khaki::logger, "epfd is not a valid file descriptor.");
			} else if (errno == EFAULT) {
				log4cppError(khaki::logger, "The memory area pointed to by events is not accessible with write permissions.");
			} else if (errno == EINTR) {
				log4cppError(khaki::logger, "epfd timeout expired.");
			} else if (errno == EINVAL) {
				log4cppError(khaki::logger, "maxevents is less than or equal to zero.");
			}
		}
	}
}