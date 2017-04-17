#ifndef KHAKI_EVENTLOOPTHREAD_H
#define KHAKI_EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include <thread>
#include <condition_variable>

namespace khaki{
	
    class EventLoopThread {
    public:
        EventLoopThread();
        ~EventLoopThread();

        EventLoop* getLoop();
        void startLoop();
    private:
        void run();
        EventLoop* loop_;
        std::thread thread_;
        std::mutex mtx_;
        std::condition_variable cond_;
    };
}

#endif //KHAKI_EVENTLOOPTHREAD_H
