#pragma once

#include "Sprite.h"
#include "StaticBody.h"
#include "GameConfiguration.h"

class SceneManager;
class Renderer;

class StaticSprite : public Sprite
{
public:
	StaticSprite(std::string goID, std::string filename, float x, float y, int r, int c, int oX = 0, int oY = 0, bool v = true, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, SDL_RendererFlip o = SDL_FLIP_NONE);
	StaticSprite(std::string goID, std::string filename, float x, float y, bool v = true, bool rot = true, double a = 0.0, float density = 1.0f, float friction = 1.0f, float restitution = 0.0f, SDL_RendererFlip o = SDL_FLIP_NONE);
	~StaticSprite();

	void update(float delta);
	void render();

	void setCamera(Camera* c);

	StaticBody* getBody();

private:
	StaticBody* staticBody;
};