#pragma once

#include "Gameloop.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

class VariableGameloop : public Gameloop
{
public:
	VariableGameloop();

	void handleEvents();
	void update(float delta);
	void render();

	void process();

private:
	float lag;
};