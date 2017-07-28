#ifndef KHAKI_TIMER_H
#define KHAKI_TIMER_H
#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <vector>
#include <memory>
#include <map>

namespace khaki {

    typedef std::function<void()> TimerCallback;
    class Timer {
    public:
        Timer(const TimerCallback& cb, unsigned long long timeout, unsigned int iv) :
            timeout_(timeout), cb_(cb), iv_(iv) {
        }
        ~Timer(){}
        unsigned int GetIv() { return iv_; }
        void AddTimeOut() { timeout_ += iv_; }
        unsigned long long GetTimeoutTime() { return timeout_; }
        void TimeOut() { cb_(); }
    private:
        unsigned int timeId;
        unsigned long long timeout_;
        unsigned int iv_;
        TimerCallback cb_;
    };

	class TimerManager {
	public:
		TimerManager();
		~TimerManager();
        
        void AddTimer(const TimerCallback& cb, unsigned long long timeout/*second*/, unsigned int iv/*second*/);
        void RemoveTimer(unsigned int timerId);

        void Run(unsigned long long timeout);
	private:
        unsigned long long ddwTimerId;
        std::multimap<unsigned long long/*timeout*/, unsigned int/*timerId*/> timerLists;
        std::map<unsigned int/*timerId*/, Timer> timerIdLists;
	};
}

#endif