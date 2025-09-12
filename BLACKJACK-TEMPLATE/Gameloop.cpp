#include "pch.h"
#include "Gameloop.h"

Uint32 Gameloop::getStartTime()
{
	return startTime;
}

float Gameloop::getDeltaTime()
{
	return delta;
}

bool Gameloop::running = false;
bool Gameloop::paused = false;
const float Gameloop::FPS = 60.0f;
const float Gameloop::DELAY_TIME = 1000.0f / FPS;