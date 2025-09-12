#include "pch.h"
#include "EventDispatcher.h"

EventDispatcher* EventDispatcher::getInstance()
{
    if (instance == nullptr)
        instance = new EventDispatcher();
    return instance;
}

void EventDispatcher::removeInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void EventDispatcher::addEventListener(const std::string& eventType, Callback callback)
{
    listeners[eventType].emplace_back(nullptr, callback);
}

void EventDispatcher::removeEventListener(const std::string& eventType, Callback callback)
{
    auto& vec = listeners[eventType];
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [&callback](const CallbackMethod& cm)
        {
            return cm.second.target<void(const Event&)>() == callback.target<void(const Event&)>();
        }), vec.end());
}

void EventDispatcher::dispatchEvent(const Event& event)
{
    const auto& vec = listeners[event.getType()];
    for (const auto& callback : vec)
    {
        if(callback.second)
            callback.second(event);
    }
}

EventDispatcher* EventDispatcher::instance = nullptr;