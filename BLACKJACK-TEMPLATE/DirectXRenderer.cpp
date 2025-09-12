#include "pch.h"
#include "DirectXRenderer.h"
#include "Window.h"
#include "SceneManager.h"

DirectXRenderer::DirectXRenderer(int d, Camera* c) : frontBuffer(nullptr), backBuffer(nullptr)
{
	driver = d;
	flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
	renderer = SDL_CreateRenderer(Window::getSDLWindow(), driver, flags);

	if (renderer)
	{
		LOG_INFO("Renderer created...");

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		frontBuffer = new FrameBuffer();
		backBuffer = new FrameBuffer();

		if (frontBuffer == nullptr)
		{
			LOG_ERROR("Could not create front buffer...");
		}

		if (backBuffer == nullptr)
		{
			LOG_ERROR("Could not create back buffer...");
		}

		camera = c;
	}
	else
		LOG_ERROR("Renderer was not created...");
}

DirectXRenderer::~DirectXRenderer()
{
	delete frontBuffer;
	delete backBuffer;
}

void DirectXRenderer::render()
{
	if (renderer)
	{
		SDL_Texture* backTexture = backBuffer->getBuffer();

		SDL_SetRenderTarget(renderer, backTexture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SceneManager::getInstance()->render();

		SDL_SetRenderTarget(renderer, nullptr);

		SDL_Texture* frontTexture = frontBuffer->getBuffer();
		SDL_RenderCopy(renderer, frontTexture, nullptr, nullptr);
		SDL_RenderPresent(renderer);

		std::swap(frontBuffer, backBuffer);
	}
}