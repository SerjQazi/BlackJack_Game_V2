#pragma once

#include "Window.h"
#include "Camera.h"

class DirectXRenderer;
class OpenGLRenderer;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	static Renderer* getInstance();
	static void removeInstance();

	virtual void render();

	static SDL_Renderer* getSDLRenderer();
	static Renderer* rendererPIMPL;

protected:
	int driver;
	Uint32 flags;
	Camera* camera;

	static SDL_Renderer* renderer;	
	static Renderer* instance;
};