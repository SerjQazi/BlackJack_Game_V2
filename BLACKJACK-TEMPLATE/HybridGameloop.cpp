#include "pch.h"
#include "HybridGameloop.h"

HybridGameloop::HybridGameloop()
{
    time = TimerManager::getInstance()->createTimer("main");
    startTime = time->getTicks();
    currentTime = startTime;
    previousTime = startTime;

    running = true;
    paused = false;

    delta = 0.0f;
    lag = 0.0f;

    time->start();
}

void HybridGameloop::handleEvents()
{
    InputManager::getInstance()->handleEvents();
}

void HybridGameloop::update(float delta)
{
    if (!paused)
        SceneManager::getInstance()->update(delta);
}

void HybridGameloop::render()
{
    if (!paused)
        Renderer::getInstance()->render();
}

void HybridGameloop::process()
{
    while (running)
    {
        currentTime = time->getTicks();

        float frameTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        lag += frameTime;

        handleEvents();

        while (lag >= DELAY_TIME / 1000.0f) 
        {
            TimerManager::getInstance()->updateAllTimers();
            update(DELAY_TIME / 1000.0f);
            lag -= DELAY_TIME / 1000.0f;
        }

        render();
    }
}