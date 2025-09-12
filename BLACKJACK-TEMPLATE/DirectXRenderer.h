#pragma once

#include "Renderer.h"
#include "FrameBuffer.h"

class Window;
class SceneManager;

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer(int d, Camera* c);
	~DirectXRenderer();

	void render();

private:
	FrameBuffer* frontBuffer;
	FrameBuffer* backBuffer;
};