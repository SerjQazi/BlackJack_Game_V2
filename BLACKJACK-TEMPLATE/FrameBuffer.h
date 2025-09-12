#pragma once

#include "Buffer.h"

class FrameBuffer : public Buffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	SDL_Texture* getBuffer();

private:
	SDL_Texture* buffer;
};