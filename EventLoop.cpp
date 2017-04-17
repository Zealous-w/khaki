#include "EventLoop.h"
#include "channel.h"

namespace khaki{

	EventLoop::EventLoop() :
		poll_(new PollEpoll()),
		time_wheel(new TimeWheel(60))
	{
		byRunning_ = true;

		cTimeWheel_ = new Channel(this, time_wheel->getTimeFd(), kReadEv);
		cTimeWheel_->OnRead([this]{ this->time_wheel->handlerRead(); });
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

	void EventLoop::loop()
	{
		while(byRunning_)
		{
			poll_->poll();
		}
	}
}