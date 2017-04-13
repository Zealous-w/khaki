//
// Created by khaki on 2017/4/3 0003.
//
#ifndef KHAKI_EVENTLOOP_H
#define KHAKI_EVENTLOOP_H
#include "poll.h"

namespace khaki{
    class PollBase;
	class PollEpoll;
	
    class EventLoop {
    public:
        EventLoop();
        ~EventLoop();

        PollEpoll* getPoll();

        void loop();
        
        void setStatus(bool status);
        virtual EventLoop* getNextLoop() { return this; }
    private:
        bool byRunning_;
        PollEpoll* poll_;
    };
}

#endif //KHAKI_EVENTLOOP_H
