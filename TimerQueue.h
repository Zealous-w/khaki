#ifndef KHAKI_TIMER_QUEUE_H
#define KHAKI_TIMER_QUEUE_H

#include <sys/time.h>
#include <queue>
#include <functional>
#include <iostream>
#include "TimerHeap.h"
#include "Util.h"

namespace khaki {

#define timer_cmp(tvp, uvp, cmp)  \
    (((tvp)->tv_sec == (uvp)->tv_sec) ?  \
        ((tvp)->tv_usec cmp (uvp)->tv_usec) : \
            ((tvp)->tv_sec cmp (uvp)->tv_sec))
    
#define timer_sub(tvp, uvp, vvp) \
    do { \
        (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;\
        (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec; \
        if ((vvp)->tv_usec < 0) { \
            (vvp)->tv_sec--; \
            (vvp)->tv_usec += 1000000;  \
        } \
    } while (0)    
    
#define timer_add(tvp, uvp, vvp) \
    do {\
    (vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec; \
    (vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;\
    if ((vvp)->tv_usec >= 1000000) { \
    (vvp)->tv_sec++; \
    (vvp)->tv_usec -= 1000000; \
    } \
    } while (0)    

#define timer_set_interval(tvp) ( (tvp->tv_sec != 0) || (tvp->tv_usec != 0) ) 

class TimerEntry {
public:
    typedef std::function<void()> EntryCallback;
    TimerEntry(uint32_t timerId, struct timeval tm, struct timeval interval, EntryCallback& cb):
        timerId_(timerId), cb_(cb) {
        tm_.tv_sec = tm.tv_sec;
        tm_.tv_usec = tm.tv_usec;
        interval_.tv_sec = interval.tv_sec;
        interval_.tv_usec = interval.tv_usec;
    }
    TimerEntry(TimerEntry& timer) {
        tm_.tv_sec = timer.tm_.tv_sec;
        tm_.tv_usec = timer.tm_.tv_usec;
        interval_.tv_sec = timer.interval_.tv_sec;
        interval_.tv_usec = timer.interval_.tv_usec;
        cb_ = timer.cb_;
        timerId_ = timer.timerId_;
    }
    ~TimerEntry() {}
    bool operator<(const TimerEntry& timer) {
        return timer_cmp(&(this->tm_), &(timer.tm_), <);
    }

    void timeout() { 
        if (cb_) 
            cb_();
        else 
            printf("bad function %d\n", timerId_); 
    }

    struct timeval tm_;
    struct timeval interval_;
    uint32_t timerId_;
    EntryCallback cb_;
};

class TimerQueue : public MinHeap<TimerEntry> {
public:
    typedef std::function<void()> TimerCallBack;
    TimerQueue() :autoTimerId_(0) {}
    ~TimerQueue(){}

    uint32_t genTimerId() { return autoTimerId_++; }
    uint32_t AddTimer(uint32_t after, uint32_t interval, TimerCallBack cb) {
        uint32_t timerId = genTimerId();
        struct timeval tm, tm_iv;
        tm.tv_sec = khaki::util::getTime() + after;
        tm.tv_usec = 0;
        tm_iv.tv_sec = interval;
        tm_iv.tv_usec = 0;
        push(new TimerEntry(timerId, tm, tm_iv, cb));
        return timerId;
    }

    uint32_t RemoveTimer(uint32_t timerId) {
        for (int idx = 0; idx < size_; ++idx) {
            auto t = heap_[idx];
            if (t->timerId_ == timerId) {
                t->cb_ = NULL;
                break;
            }
        }
    }

    void update(struct timeval& tm) {
        //this->show();
        std::vector<TimerEntry*> vAddEntry;
        while (!empty()) {
            auto t = front();
            if (timer_cmp(&t->tm_, &tm, <=)) {
                t->timeout();
    
                if (timer_set_interval((&t->interval_))) {
                    timer_add(&tm, &t->interval_, &t->tm_);
                    //std::cout << "tm : " << t->tm_.tv_sec << " " << t->tm_.tv_usec << " iv :" << t->interval_.tv_sec << " " << t->interval_.tv_usec << std::endl;
                    auto entry = new TimerEntry(*t);
                    entry->timerId_ = genTimerId();
                    vAddEntry.push_back(entry);
                }
    
                pop();
            } else {
                break;
            }
        }
    
        for (auto iter : vAddEntry) {
            push(iter);
            //std::cout << "size : " << size() << std::endl;
        }
    }

    void show() {
        for (int idx = 0; idx < size_; ++idx) {
            auto iter = heap_[idx];
            std::cout << "[" << iter->tm_.tv_sec << ", " << iter->interval_.tv_sec << ", " << iter->timerId_ << std::endl;
        }
    }
private:
    uint32_t autoTimerId_;
};

}

#endif