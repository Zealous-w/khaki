//
// Created by khaki on 2017/4/3 0003.
//
#ifndef KHAKI_EVENTLOOP_H
#define KHAKI_EVENTLOOP_H

#include "poll.h"
#include "time_wheel.h"

#include <memory>

namespace khaki{
    class PollBase;
	class PollEpoll;
    class TimeWheel;
    class Channel;

    class EventLoop {
    public:
        EventLoop();
        ~EventLoop();

        PollEpoll* getPoll();

        void loop();

        void setStatus(bool status);
        std::shared_ptr<TimeWheel>& getTimeWheelPtr() { return time_wheel; }
        virtual EventLoop* getNextLoop() { return this; }

    private:
        bool byRunning_;
        PollEpoll* poll_;
        Channel* cTimeWheel_;
        std::shared_ptr<TimeWheel> time_wheel;
    };
}

#endif //KHAKI_EVENTLOOP_H
