#pragma once

#include "SDL_ttf.h"

#include "GameObject.h"
#include "Font.h"

class ResourceManager;
class Renderer;

class Text : public GameObject
{
public:
	Text(std::string name, std::string f, std::string t = "", float x = 0.0f, float y = 0.0f, int s = 1, SDL_Color c = {0, 0, 0, 255}, bool v = true, double a = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	Text(const Text& other);
	~Text();

	Text* clone();

	void update(float);
	void render();

	void setText(std::string t);
	void setColor(SDL_Color c);
	void setVisible(bool v);

	glm::vec2 position;
	int width;
	int height;
	bool visible;
	double angle;
	SDL_RendererFlip orientation;

	Font font;
	std::string text;

private:
	SDL_Texture* texture;
};
