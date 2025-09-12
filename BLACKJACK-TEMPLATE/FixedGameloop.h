#pragma once

#include "Gameloop.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

class FixedGameloop : public Gameloop
{
public:
	FixedGameloop();

	void handleEvents();
	void update(float delta);
	void render();

	void process();
};