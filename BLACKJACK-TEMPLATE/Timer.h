#pragma once

class Timer
{
    using Callback = std::function<void()>;

    struct TimedEvent
    {
        int id;
        Callback callback;
        std::chrono::milliseconds interval;
        std::chrono::time_point<std::chrono::steady_clock> nextCall;
        bool repeat;
        bool active;
    };

public:
    Timer(std::string id);

    void update();
    
    void start();
    void stop();
    void pause();
    void resume();

    Uint32 getTicks();
    bool isStarted() const;
    bool isPaused() const;

    template <typename T>
    int setTimeout(T* instance, void(T::* method)(), std::chrono::milliseconds delay)
    {
        auto callback = std::bind(method, instance);
        return setTimeout(callback, delay);
    }

    template <typename T>
    int setInterval(T* instance, void(T::* method)(), std::chrono::milliseconds interval)
    {
        auto callback = std::bind(method, instance);
        return setInterval(callback, interval);
    }

    int setTimeout(Callback callback, std::chrono::milliseconds delay);
    int setInterval(Callback callback, std::chrono::milliseconds interval);
    void clearTimeout(int id);
    void clearInterval(int id);

    std::string getID();

private:
    std::string id;

    bool started;
    bool paused;

    std::chrono::time_point<std::chrono::steady_clock> startTicks;
    std::chrono::time_point<std::chrono::steady_clock> pausedTicks;
    std::chrono::milliseconds pausedDuration;
    
    std::vector<TimedEvent> events;
    int nextEventId;
};