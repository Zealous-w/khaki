//
// Created by khaki on 2017/4/3 0003.
//
#ifndef KHAKI_EVENTLOOP_H
#define KHAKI_EVENTLOOP_H

#include "PollEpoll.h"
#include "TimeWheel.h"
#include "Timer.h"

#include <memory>

namespace khaki{
    class PollBase;
	class PollEpoll;
    class TimeWheel;
    class Channel;

    class EventLoop {
    public:
        typedef std::function<void()> EventCallback;
        EventLoop();
        ~EventLoop();

        PollEpoll* getPoll();

        void loop();

        void setStatus(bool status);
        std::shared_ptr<TimeWheel>& getTimeWheelPtr() { return time_wheel; }
        virtual EventLoop* getNextLoop() { return this; }
        bool isInLoopThread() { return id_ == std::this_thread::get_id(); }
        void executeInLoop(const EventCallback& cb);
        void handlerWakeUpRead();
        TimerManager* getTimer() { return &timerM_; }
    private:
        bool byRunning_;
        std::mutex mtx_;
        PollEpoll* poll_;
        Channel* cTimeWheel_;
        int wakeupFd_;
        Channel* cWeakUp_;
        std::thread::id id_;
        std::shared_ptr<TimeWheel> time_wheel;
        std::vector<EventCallback> vCallback_;
        TimerManager timerM_;
    };
}

#endif //KHAKI_EVENTLOOP_H
