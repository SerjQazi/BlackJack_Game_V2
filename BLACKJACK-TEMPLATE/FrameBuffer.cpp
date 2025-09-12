#include "pch.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "GameConfiguration.h"

FrameBuffer::FrameBuffer()
{
	buffer = SDL_CreateTexture(Renderer::getSDLRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, GameConfiguration::SCREEN_WIDTH, GameConfiguration::SCREEN_HEIGHT);

	if (buffer == nullptr)
	{
		LOG_ERROR("Error: Could not create back buffer...");
	}
}

FrameBuffer::~FrameBuffer()
{
	SDL_DestroyTexture(buffer);
}

SDL_Texture* FrameBuffer::getBuffer()
{
	return buffer;
}