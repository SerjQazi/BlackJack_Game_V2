#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "SpriteConfiguration.h"

class Renderer;
class ResourceManager;
class AnimationManager;
class ConfigurationManager;

class Sprite : public GameObject
{
public:
	Sprite(std::string goID, std::string filename, float x, float y, int r, int c, int oX = 0, int oY = 0, bool v = true, double a = 0.0, SDL_RendererFlip o = SDL_FLIP_NONE);
	Sprite(std::string goID, std::string f, float x, float y, bool v = true, double a = 0.0, SDL_RendererFlip o = SDL_FLIP_NONE);
	Sprite(const Sprite& other);
	~Sprite();

	Sprite* clone();

	void update(float);
	void render();

	void addAnimation(const std::string& name, const Animation& animation);
	void addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps = 0.0f, bool loop = true, bool reverse = false, SDL_RendererFlip orientation = SDL_FLIP_NONE);
	void removeAnimation(const std::string& name);
	
	void play(const std::string& name);
	void play(std::string name, float f, bool l = false, bool r = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void stop();

	void setFPS(std::string goID, float fps);

	glm::vec2 position;
	int width;
	int height;
	int rows;
	int cols;
	int offsetX;
	int offsetY;
	bool visible;
	double angle;
	SDL_RendererFlip orientation;
	
	bool animating;

	std::string filename;

protected:
	SDL_Texture* texture;
	Animation* currentAnimation;
};