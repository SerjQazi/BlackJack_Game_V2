#pragma once

#include "Renderer.h"

class Window;

class OpenGLRenderer : public Renderer
{
public:
	OpenGLRenderer(int d, Camera* c);
	~OpenGLRenderer();

	void render();

	static SDL_GLContext getGLContext();

private:
	static SDL_GLContext glContext;
};