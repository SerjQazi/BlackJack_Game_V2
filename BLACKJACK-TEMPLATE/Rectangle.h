#pragma once

#include "GameObject.h"
#include "Renderer.h"

class Rectangle : public GameObject
{
public:
	Rectangle(std::string id, float x, float y, int w, int h, SDL_Color c = { 0x00, 0x00, 0x00, 0x00 });
	Rectangle(std::string id, glm::vec2 p, int w, int h, SDL_Color c = { 0x00, 0x00, 0x00, 0x00 });
	~Rectangle();

	void update(float delta);
	void render();

	glm::vec2 position;
	int width;
	int height;
	SDL_Color color;
};