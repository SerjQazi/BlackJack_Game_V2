#include "pch.h"

#include "Text.h"
#include "ResourceManager.h"
#include "Renderer.h"

Text::Text(std::string goID, std::string f, std::string t, float x, float y, int s, SDL_Color c, bool v, double a, SDL_RendererFlip flip) :
	text(t), position{ x, y }, visible(v), angle(a), orientation(flip), font(f, s, c)
{
	id = goID;

	LOG_INFO("Creating text ", id, "...");

	texture = ResourceManager::getInstance()->addTextTexture(id, text, font);

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Text::Text(const Text& other) : 
	position(other.position), visible(other.visible), angle(other.angle), orientation(other.orientation), font(other.font)
{
	id = other.id + "-clone";

	LOG_INFO("Cloning texts ", id, "...");

	texture = ResourceManager::getInstance()->addTextTexture(id, text, font);

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Text::~Text()
{
	LOG_INFO("Removing text ", id, "...");

	ResourceManager::getInstance()->removeTexture(id);
}

Text* Text::clone()
{
	return new Text(*this);
}

void Text::update(float delta)
{

}

void Text::render()
{
	if (visible)
	{
		if (camera)
		{
			int screenX = static_cast<int>((position.x - camera->getViewPort().x) * camera->getZoom());
			int screenY = static_cast<int>((position.y - camera->getViewPort().y) * camera->getZoom());

			int transformedWidth = static_cast<int>(width * camera->getZoom());
			int transformedHeight = static_cast<int>(height * camera->getZoom());

			SDL_Rect dest = { screenX, screenY, transformedWidth, transformedHeight };
			SDL_RenderCopyEx(Renderer::getSDLRenderer(), texture, NULL, &dest, angle, nullptr, orientation);
		}
		else
		{
			SDL_Rect dest = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
			SDL_RenderCopyEx(Renderer::getSDLRenderer(), texture, NULL, &dest, angle, nullptr, orientation);
		}
	}
}

void Text::setText(std::string t)
{
	text = t;
	texture = ResourceManager::updateTextTexture(id, text, font);
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Text::setColor(SDL_Color c)
{
	font.setColor(c.r, c.g, c.b, c.a);
}

void Text::setVisible(bool v)
{
	visible = v;
}