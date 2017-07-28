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
        void TimeOut() { cb_(); }
    private:
        unsigned int timeId;
        unsigned long long timeout_;
        unsigned int iv_;
        TimerCallback cb_;
    };

	class TimerManager {
	public:
		TimerManager(int size);
		~TimerManager();

        void AddTimer(const TimerCallback& cb, unsigned long long timeout, unsigned int iv);
        void RemoveTimer(unsigned int timerId);
	private:
        std::map<unsigned long long/*timeout*/, unsigned int/*timerId*/> timerLists;
        std::map<unsigned int/*timerId*/, Timer> timerIdLists;
	};
}

#endif