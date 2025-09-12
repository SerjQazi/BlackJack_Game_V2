#include "pch.h"
#include "DefaultRenderer.h"
#include "Window.h"
#include "SceneManager.h"

DefaultRenderer::DefaultRenderer(int d, Camera* c)
{
	driver = d;
	flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
	renderer = SDL_CreateRenderer(Window::getSDLWindow(), driver, flags);

	if (renderer)
	{
		LOG_INFO("Renderer created...");

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		camera = c;
	}
	else
		LOG_INFO("Renderer was not created...");
}

DefaultRenderer::~DefaultRenderer()
{ }

void DefaultRenderer::render()
{
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Rect cameraViewPort = camera->getViewPort();
		SDL_RenderSetViewport(renderer, &cameraViewPort);

		SceneManager::getInstance()->render();

		SDL_RenderPresent(renderer);
	}
}