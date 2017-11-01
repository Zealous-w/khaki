#ifndef KHAKI_TIMER_H
#define KHAKI_TIMER_H
#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <vector>
#include <memory>
#include <map>
#include "Log.h"

namespace khaki {

    typedef std::function<void()> TimerCallback;
    class Timer {
    public:
        Timer(const TimerCallback& cb, unsigned int timeout, unsigned int iv) :
            timeout_(timeout), cb_(cb), iv_(iv) {
        }
        ~Timer(){}
        unsigned int GetIv() { return iv_; }
        void AddTimeOut() { timeout_ += iv_; }
        unsigned int GetTimeoutTime() { return timeout_; }
        void TimeOut() { if (cb_) cb_(); else log4cppError(logger, "bad function"); }
    private:
        unsigned int timeId;
        unsigned int timeout_;
        unsigned int iv_;
        TimerCallback cb_;
    };

	class TimerManager {
	public:
		TimerManager();
		~TimerManager();
        
        void AddTimer(const TimerCallback& cb, unsigned int timeout/*second*/, unsigned int iv/*second*/);
        void RemoveTimer(unsigned int timerId);

        void Run(unsigned int timeout);
	private:
        unsigned long long ddwTimerId;
        std::multimap<unsigned int/*timeout*/, unsigned int/*timerId*/> timerLists;
        std::map<unsigned int/*timerId*/, Timer> timerIdLists;
	};
}

#endif