#include <sys/eventfd.h>
#include <stdlib.h>

#include "EventLoop.h"
#include "Channel.h"

namespace khaki{

	EventLoop::EventLoop() :
		poll_(new PollEpoll()),
		id_(std::this_thread::get_id()),
		time_wheel(new TimeWheel(120)),
		wakeupFd_(::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC)),
		byRunning_(true)
	{
		cTimeWheel_ = new Channel(this, time_wheel->getTimeFd());
		cTimeWheel_->OnRead([this]{ this->time_wheel->handlerRead(); });
		cTimeWheel_->enableRead(true);
		
		cWeakUp_ = new Channel(this, wakeupFd_);
		cWeakUp_->OnRead(std::bind(&EventLoop::handlerWakeUpRead, this));
		cWeakUp_->enableRead(true);
	}

	EventLoop::~EventLoop()
	{
		delete cTimeWheel_;
		delete poll_;
	}

	void EventLoop::setStatus(bool status)
	{
		byRunning_ = status;
	}

	PollEpoll* EventLoop::getPoll()
	{
		return poll_;
	}

	void EventLoop::executeInLoop(const EventCallback& cb)
	{
		if (isInLoopThread()) { cb(); }
		else
		{
			mCallback_.push(cb);

			uint64_t one = 1;
			write(wakeupFd_, &one, sizeof one );
		}
	}

	void EventLoop::handlerWakeUpRead()
	{
		uint64_t one = 1;

		int n = read(wakeupFd_, &one, sizeof one);
		if (n != sizeof one)
		{
			log4cppDebug(logger, "read wakeup fd error");
		}
		
		if (mCallback_.size() > 0) {
			std::queue<EventCallback> tmpQueue = mCallback_.popAll();
			while ( !tmpQueue.empty() ) {
				EventCallback cb = tmpQueue.front();
				if (cb) cb();
				else {
					log4cppDebug(logger, "EventLoop::handlerWakeUpRead ERROR");
				}
				tmpQueue.pop();
			}
		}
	}

	void EventLoop::loop()
	{
		while(byRunning_)
		{
			poll_->poll();
			timerM_.Run(util::getTime());
		}
	}
}