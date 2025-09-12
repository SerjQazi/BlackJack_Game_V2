#include "pch.h"
#include "FrameGameloop.h"

FrameGameloop::FrameGameloop()
{
	time = TimerManager::getInstance()->createTimer("main");
	startTime = time->getTicks();
	currentTime = startTime;
	previousTime = startTime;

	running = true;
	paused = false;

	delta = DELAY_TIME;
}

void FrameGameloop::handleEvents()
{
	InputManager::getInstance()->handleEvents();
}

void FrameGameloop::update(float delta)
{
	if (!paused)
		SceneManager::getInstance()->update(delta);
}

void FrameGameloop::render()
{
	if (!paused)
		Renderer::getInstance()->render();
}

void FrameGameloop::process()
{
	while (running)
	{
		handleEvents();
		update(delta / 1000.0f);
		TimerManager::getInstance()->updateAllTimers();
		render();
	}
}