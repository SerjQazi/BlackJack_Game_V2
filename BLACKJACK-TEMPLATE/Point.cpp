#include "pch.h"
#include "Point.h"

Point::Point(std::string goID, float x, float y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) : position(x, y), r(red), g(green), b(blue), a(alpha), visible(true)
{
	id = goID;
}

void Point::update(float delta)
{

}

void Point::render()
{
	if (visible)
	{
		SDL_Renderer* renderer = Renderer::getSDLRenderer();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderDrawPoint(renderer, position.x, position.y);
	}
}

void Point::setVisibility(bool v)
{
	visible = v;
}

void Point::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Renderer* renderer = Renderer::getSDLRenderer();

	r = red;
	g = green;
	b = blue;
	a = alpha;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}