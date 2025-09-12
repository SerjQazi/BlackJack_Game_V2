#pragma once

#include "Timer.h"

class TimerManager
{
public:
    static TimerManager* getInstance();
    static void removeInstance();

    Timer* createTimer(std::string id);
    void removeTimer(std::string id);
    void removeTimer(Timer* timer);
    Timer* findTimer(std::string id);

    void updateAllTimers();

private:
    TimerManager();
    ~TimerManager();

    std::vector<Timer*> timers;

    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;

    static TimerManager* instance;
};