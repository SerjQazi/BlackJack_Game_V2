#include "pch.h"
#include "Line.h"

Line::Line(std::string goID, float x1, float y1, float x2, float y2, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) : p1(x1, y1), p2(x2, y2), r(red), g(green), b(blue), a(alpha), visible(true)
{
	id = goID;
}

void Line::update(float delta)
{

}

void Line::render()
{
	if (visible)
	{
		SDL_Renderer* renderer = Renderer::getSDLRenderer();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	}
}

void Line::setVisibility(bool v)
{
	visible = v;
}

void Line::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Renderer* renderer = Renderer::getSDLRenderer();

	r = red;
	g = green;
	b = blue;
	a = alpha;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}