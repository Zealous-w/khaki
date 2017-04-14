#ifndef KHAKI_EVENTLOOPTHREAD_H
#define KHAKI_EVENTLOOPTHREAD_H
#include "EventLoop.h"
#include <thread>

namespace khaki{
	
    class EventLoopThread {
    public:
        EventLoopThread();
        ~EventLoopThread();

        EventLoop* getLoop();
        void loopThread();
    private:
        void run();
        EventLoop* loop_;
        std::thread thread_;
        
    };
}

#endif //KHAKI_EVENTLOOPTHREAD_H
