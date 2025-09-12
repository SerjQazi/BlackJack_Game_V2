#include "pch.h"
#include "Box.h"

Box::Box(std::string goID, float x, float y, float w, float h, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) : position(x, y), w(w), h(h), r(red), g(green), b(blue), a(alpha), visible(true)
{
	id = goID;
}

void Box::update(float delta)
{

}

void Box::render()
{
	if (visible)
	{
		SDL_Renderer* renderer = Renderer::getSDLRenderer();

		SDL_Rect dest = { position.x, position.y, w, h };

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderFillRect(renderer, &dest);
		SDL_RenderDrawRect(renderer, &dest);
	}
}

void Box::setVisibility(bool v)
{
	visible = v;
}

void Box::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Renderer* renderer = Renderer::getSDLRenderer();

	r = red;
	g = green;
	b = blue;
	a = alpha;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}