#pragma once

#include "Event.h"

class EventDispatcher
{
public:
    using Callback = std::function<void(const Event&)>;
    using CallbackMethod = std::pair<void*, Callback>;

    static EventDispatcher* getInstance();
    static void removeInstance();

    void addEventListener(const std::string& eventType, Callback callback);
    void removeEventListener(const std::string& eventType, Callback callback);

    template <typename T, typename E>
    void addEventListener(const std::string& eventType, T* instance, void (T::* method)(const E&))
    {
        static_assert(std::is_base_of<Event, E>::value, "Error: parameter is not an event...");

        auto callback = [instance, method](const Event& event)
            {
                const E* derivedEvent = dynamic_cast<const E*>(&event);
                if (derivedEvent)
                    (instance->*method)(*derivedEvent);
            };

        listeners[eventType].emplace_back(static_cast<void*>(instance), callback);
    }

    template <typename T, typename E>
    void removeEventListener(const std::string& eventType, T* instance, void (T::* method)(const E&))
    {
        auto& vec = listeners[eventType];
        std::function<void(const E&)> func = std::bind(method, instance, std::placeholders::_1);
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [instance, method, func](const CallbackMethod& callback)
            {
                return callback.first == static_cast<void*>(instance) && callback.second.target<void(const Event&)>() == func.target<void(const Event&)>();
            }), vec.end());
    }

    void dispatchEvent(const Event& event);

private:
    std::unordered_map<std::string, std::vector<CallbackMethod>> listeners;

    static EventDispatcher* instance;
};