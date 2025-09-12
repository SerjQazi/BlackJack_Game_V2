#include "pch.h"
#include "Timer.h"

Timer::Timer(std::string id) : id(id), started(false), paused(false), pausedDuration(0), nextEventId(0) 
{ 
    LOG_INFO("Timer ", id, " created...");
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = std::chrono::steady_clock::now();
    pausedDuration = std::chrono::milliseconds::zero();
}

void Timer::stop()
{
    started = false;
    paused = false;
    events.clear();
}

void Timer::pause()
{
    if (started && !paused)
    {
        paused = true;
        pausedTicks = std::chrono::steady_clock::now();
    }
}

void Timer::resume()
{
    if (paused)
    {
        paused = false;
        auto now = std::chrono::steady_clock::now();
        pausedDuration += std::chrono::duration_cast<std::chrono::milliseconds>(now - pausedTicks);
    }
}

Uint32 Timer::getTicks()
{
    if (started)
    {
        if (paused)
        {
            return static_cast<Uint32>(std::chrono::duration_cast<std::chrono::milliseconds>(pausedTicks - startTicks).count());
        }
        else
        {
            return static_cast<Uint32>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTicks - pausedDuration).count());
        }
    }
    return 0;
}

bool Timer::isStarted() const
{
    return started;
}

bool Timer::isPaused() const
{
    return paused;
}

int Timer::setTimeout(Callback callback, std::chrono::milliseconds delay)
{
    int id = nextEventId++;
    events.push_back({ id, callback, delay, std::chrono::steady_clock::now() + delay, false, true });
    return id;
}

int Timer::setInterval(Callback callback, std::chrono::milliseconds interval)
{
    int id = nextEventId++;
    events.push_back({ id, callback, interval, std::chrono::steady_clock::now() + interval, true, true });
    return id;
}

void Timer::clearTimeout(int id)
{
    for (auto& event : events)
    {
        if (event.id == id && !event.repeat)
        {
            event.active = false;
            break;
        }
    }
}

void Timer::clearInterval(int id)
{
    for (auto& event : events)
    {
        if (event.id == id && event.repeat)
        {
            event.active = false;
            break;
        }
    }
}

void Timer::update()
{
    if (!started || paused)
        return;

    auto now = std::chrono::steady_clock::now();
    for (auto& event : events)
    {
        if (event.active && now >= event.nextCall)
        {
            event.callback();
            if (event.repeat)
            {
                event.nextCall = now + event.interval;
            }
            else
            {
                event.active = false;
            }
        }
    }

    if (!events.empty())
    {
        auto it = events.begin();
        while (it != events.end())
        {
            if (!(*it).active)
                it = events.erase(it);
            else
                ++it;
        }
    }
}

std::string Timer::getID()
{
    return id;
}