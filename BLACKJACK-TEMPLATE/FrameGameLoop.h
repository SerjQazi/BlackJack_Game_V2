#pragma once

#include "Gameloop.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

class FrameGameloop : public Gameloop
{
public:
	FrameGameloop();

	void handleEvents();
	void update(float delta);
	void render();

	void process();
};