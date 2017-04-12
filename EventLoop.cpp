#include "EventLoop.h"

namespace khaki{

	EventLoop::EventLoop() :
		poll_(new PollEpoll())
	{
		byRunning_ = false;
	}

	EventLoop::~EventLoop()
	{
		delete poll_;
	}

	PollEpoll* EventLoop::getPoll()
	{
		return poll_;
	}

	void EventLoop::loop()
	{
		while(!byRunning_)
		{
			poll_->poll();
		}
	}
}