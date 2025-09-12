#pragma once

#include "Renderer.h"

class Window;
class SceneManager;

class DefaultRenderer : public Renderer
{
public:
	DefaultRenderer(int d, Camera* c);
	~DefaultRenderer();

	void render();
};