#pragma once

#include "OpenGLVertex.h"
#include "GameConfiguration.h"

class OpenGLQuad
{
public:
	OpenGLQuad(float x, float y, float frameWidth, float frameHeight, float width, float height);
	OpenGLQuad(float x, float y, float frameWidth, float frameHeight, float width, float height, int currentFrame);
	~OpenGLQuad();

	std::vector<OpenGLVertex> getVertices() const;

	void transform(float x, float y, float frameWidth, float frameHeight, float width, float height, int currentFrame);
	void transform(float x, float y, float frameWidth, float height, SDL_Rect frame, bool flip);

private:
	std::vector<OpenGLVertex> vertices;
};