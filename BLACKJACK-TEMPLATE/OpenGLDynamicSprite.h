#pragma once

#include "OpenGLSprite.h"
#include "DynamicBody.h"

class SceneManager;

class OpenGLDynamicSprite : public OpenGLSprite
{
public:
	OpenGLDynamicSprite(std::string goID, std::string filename, float x, float y, float width, float height, std::string vertexFilename, std::string fragFilename, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, bool flip = false);
	OpenGLDynamicSprite(std::string goID, std::string filename, float x, float y, std::string vertexFilename, std::string fragFilename, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, bool flip = false);
	~OpenGLDynamicSprite();

	void update(float delta);
	void render();

	DynamicBody* getBody();

private:
	DynamicBody* dynamicBody;
};