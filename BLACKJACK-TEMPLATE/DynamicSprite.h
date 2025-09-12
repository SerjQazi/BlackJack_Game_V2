#pragma once

#include "Sprite.h"
#include "DynamicBody.h"
#include "GameConfiguration.h"

class SceneManager;
class Renderer;

class DynamicSprite : public Sprite
{
public:
	DynamicSprite(std::string goID, std::string filename, float x, float y, int r, int c, int oX = 0, int oY = 0, bool v = true, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, SDL_RendererFlip o = SDL_FLIP_NONE);
	DynamicSprite(std::string goID, std::string filename, float x, float y, bool v = true, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, SDL_RendererFlip o = SDL_FLIP_NONE);
	~DynamicSprite();

	void update(float delta);
	void render();

	void setCamera(Camera* c);

	DynamicBody* getBody();

private:
	DynamicBody* dynamicBody;
};