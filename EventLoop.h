//
// Created by khaki on 2017/4/3 0003.
//
#ifndef KHAKI_EVENTLOOP_H
#define KHAKI_EVENTLOOP_H

#include "PollEpoll.h"
#include "TimeWheel.h"
#include "Timer.h"
#include "Queue.h"

#include <atomic>
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
        void stop() { byRunning_ = false; uint64_t one = 1; write(wakeupFd_, &one, sizeof one ); }
        TimerManager* getTimer() { return &timerM_; }
    private:
        std::atomic<bool> byRunning_;
        PollEpoll* poll_;
        Channel* cTimeWheel_;
        int wakeupFd_;
        Channel* cWeakUp_;
        std::thread::id id_;
        std::shared_ptr<TimeWheel> time_wheel;
        queue<EventCallback> mCallback_;
        TimerManager timerM_;
    };
}

#endif //KHAKI_EVENTLOOP_H
