#include "Timer.h"

namespace khaki {
TimerManager::TimerManager() {
    ddwTimerId = 0;
}

TimerManager::~TimerManager() {

}

void TimerManager::AddTimer(const TimerCallback& cb, unsigned int timeout, unsigned int iv) {
    Timer timer(cb, timeout, iv);
    ddwTimerId++;
    timerLists.insert(std::make_pair(timeout, ddwTimerId));
    if (timerIdLists.find(ddwTimerId) != timerIdLists.end()) {
        timerIdLists.erase(ddwTimerId);
    }
    timerIdLists.insert(std::make_pair(ddwTimerId, timer)); //
}

void TimerManager::RemoveTimer(unsigned int timerId) {
    timerIdLists.erase(timerId);
}

void TimerManager::Run(unsigned int timeout) {
    std::map<unsigned int/*timerId*/, Timer> addMap;
    for ( auto iter = timerLists.begin(); 
            iter != timerLists.end(); ) {
        if (iter->first <= timeout) {
            auto tIter = timerIdLists.find(iter->second);
            if (tIter != timerIdLists.end()) {
                tIter->second.TimeOut();
                if ( tIter->second.GetIv() != 0 ) {
                    tIter->second.AddTimeOut();
                    addMap.insert(std::make_pair(iter->second, tIter->second));
                } else {
                    timerIdLists.erase(iter->second);
                }
            }
            iter = timerLists.erase(iter);
        } else {
            ++iter;
        }
    }

    for ( auto iter = addMap.begin(); iter != addMap.end(); ++iter ) {
        timerLists.insert(std::make_pair(iter->second.GetTimeoutTime(), iter->first));
    }

    //log4cppDebug(logger, "timerIdLists:%d", timerIdLists.size());
}

}
