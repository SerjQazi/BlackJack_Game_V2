#pragma once

#include "GameConfiguration.h"
#include "Camera.h"

class Renderer;
class RendererFactory;
class Gameloop;
class Engine;
class SceneManager;

class Window
{
public:
	Window(const GameConfiguration& config);
	Window(std::string t, int x, int y, int w, int h, int worldWidth, int worldHeight, float zoom, Uint32 flags, std::string driver);
	~Window();

	static Camera* getCamera();

	static SDL_Window* getSDLWindow();

private:
	std::string title;
	glm::vec2 position;
	int width;
	int height;
	static Camera* camera;

	static SDL_Window* window;
};