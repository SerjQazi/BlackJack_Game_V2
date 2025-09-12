#include "pch.h"
#include "VariableGameloop.h"

VariableGameloop::VariableGameloop()
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

void VariableGameloop::handleEvents()
{
    InputManager::getInstance()->handleEvents();
}

void VariableGameloop::update(float delta)
{
    if (!paused)
        SceneManager::getInstance()->update(delta);
}

void VariableGameloop::render()
{
    if (!paused)
        Renderer::getInstance()->render();
}

void VariableGameloop::process()
{
    while (running)
    {
        currentTime = time->getTicks();
        delta = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        handleEvents();
        update(delta);
        TimerManager::getInstance()->updateAllTimers();
        render();
    }
}