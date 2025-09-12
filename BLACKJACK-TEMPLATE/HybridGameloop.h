#pragma once

#include "Gameloop.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"

class HybridGameloop : public Gameloop
{
public:
	HybridGameloop();

	void handleEvents();
	void update(float delta);
	void render();

	void process();

private:
	float lag;
};