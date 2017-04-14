#include "EventLoopThread.h"

namespace khaki {
    EventLoopThread::EventLoopThread():
        loop_(NULL),
        thread_(&EventLoopThread::run, this)
    {

    }

    EventLoopThread::~EventLoopThread()
    {
        if ( thread_.joinable() ) thread_.join();
        if ( loop_ ) delete loop_;
    }

    EventLoop* EventLoopThread::getLoop()
    {
        return loop_;
    }

    void EventLoopThread::loopThread()
    {
    }

    void EventLoopThread::run()
    {

        loop_->loop();
    }
}