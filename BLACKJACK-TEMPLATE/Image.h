#pragma once

#include "GameObject.h"

class Renderer;
class ResourceManager;

class Image : public GameObject
{
public:
	Image(std::string goID, std::string f, float x, float y, bool v = true, double a = 0.0, SDL_RendererFlip o = SDL_FLIP_NONE);
	Image(std::string goID, std::string f, float x, float y, int w, int h, bool v = true, double a = 0.0, SDL_RendererFlip o = SDL_FLIP_NONE);
	~Image();

	void update(float);
	void render();

	glm::vec2 position;
	int width;
	int height;
	double angle;
	std::string filename;

private:
	SDL_Texture* texture;
	bool visible;
	SDL_RendererFlip orientation;
};