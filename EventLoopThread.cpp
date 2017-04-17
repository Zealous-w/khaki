#include "EventLoopThread.h"
#include "log.h"

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

    void EventLoopThread::startLoop()
    {
        std::unique_lock<std::mutex> lck(mtx_);
        loop_ = new EventLoop();
        cond_.notify_all();
    }

    void EventLoopThread::run()
    {
        {
            std::unique_lock<std::mutex> lck(mtx_);
            while ( loop_ == NULL ) cond_.wait(lck);
        }

        loop_->loop();
    }
}