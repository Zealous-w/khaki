#include "EventLoop.h"

namespace khaki{

	EventLoop::EventLoop() :
		poll_(new PollEpoll())
	{
		byRunning_ = true;
	}

	EventLoop::~EventLoop()
	{
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