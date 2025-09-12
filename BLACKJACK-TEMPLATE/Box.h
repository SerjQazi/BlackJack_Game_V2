#pragma once

#include "GameObject.h"
#include "Renderer.h"

class Box : public GameObject
{
public:
	Box(std::string, float, float, float, float, Uint8 = 255, Uint8 = 255, Uint8 = 255, Uint8 = 255);

	void update(float delta);
	void render();

	void setColor(Uint8 = 255, Uint8 = 255, Uint8 = 255, Uint8 = 255);
	void setVisibility(bool v = true);

	glm::vec2 position;

private:
	int w;
	int h;

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	bool visible;
};
