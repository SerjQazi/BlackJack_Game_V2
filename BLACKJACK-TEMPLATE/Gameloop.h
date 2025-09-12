#pragma once

#include "Timer.h"

class Gameloop
{
public:
    virtual ~Gameloop() = default;

    virtual void process() = 0;

    virtual void handleEvents() = 0;
    virtual void update(float delta) = 0;
    virtual void render() = 0;

    Uint32 getStartTime();
    float getDeltaTime();

    static bool running;
    static bool paused;

    static const float FPS;
    static const float DELAY_TIME;

protected:
    Uint32 startTime;
    Uint32 currentTime;
    Uint32 previousTime;
    float delta;
    Timer* time;
};