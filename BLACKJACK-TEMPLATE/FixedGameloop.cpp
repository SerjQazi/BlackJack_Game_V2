#include "pch.h"
#include "FixedGameloop.h"

FixedGameloop::FixedGameloop()
{
	time = TimerManager::getInstance()->createTimer("main");
	startTime = time->getTicks();
	currentTime = startTime;
	previousTime = startTime;

	running = false;
	paused = false;

	delta = 0.0f;

	time->start();
}

void FixedGameloop::handleEvents()
{
	InputManager::getInstance()->handleEvents();
}

void FixedGameloop::update(float delta)
{
	if (!paused)
		SceneManager::getInstance()->update(delta);
}

void FixedGameloop::render()
{
	if (!paused)
		Renderer::getInstance()->render();
}

void FixedGameloop::process()
{
	while (running)
	{
		delta = (currentTime - previousTime) / 1000.0f;
		previousTime = currentTime;
		currentTime = time->getTicks();

		handleEvents();
		update(delta);
		TimerManager::getInstance()->updateAllTimers();
		render();

		int elapsed = time->getTicks() - currentTime;

		if (elapsed > 0 && elapsed < Gameloop::DELAY_TIME)
			SDL_Delay(static_cast<Uint32>(Gameloop::DELAY_TIME - elapsed));
	}
}