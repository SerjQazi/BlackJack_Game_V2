#include "pch.h"
#include "TimerManager.h"

TimerManager::TimerManager() 
{ 
    LOG_INFO("Initializing time manager...");
}

TimerManager::~TimerManager() 
{
    LOG_INFO("Removing timers...");
    for (auto item : timers)
        delete item;
}

TimerManager* TimerManager::getInstance()
{
    if(instance == nullptr)
        instance = new TimerManager();
    return instance;
}

void TimerManager::removeInstance()
{
    if (instance)
        delete instance;
}

Timer* TimerManager::createTimer(std::string id)
{
    LOG_INFO("Timer created...");
    auto timer = new Timer(id);
    timers.push_back(timer);
    return timer;
}

void TimerManager::removeTimer(std::string id)
{
    auto it = timers.begin();
    while (it != timers.end())
    {
        if((*it)->getID() == id)
        { 
            delete* it;
            timers.erase(it);
            break;
        }
        else
            ++it;
    }
}

void TimerManager::removeTimer(Timer* timer)
{
    auto it = std::find(timers.begin(), timers.end(), timer);
    if (it != timers.end())
    {
        delete* it;
        timers.erase(it);
    }
}

Timer* TimerManager::findTimer(std::string id)
{
    auto it = timers.begin();
    if (it != timers.end())
    {
        if((*it)->getID() == id)
            return *it;

        ++it;
    }

    return nullptr;
}

void TimerManager::updateAllTimers()
{
    for (auto& timer : timers)
    {
        timer->update();
    }
}

TimerManager* TimerManager::instance = nullptr;