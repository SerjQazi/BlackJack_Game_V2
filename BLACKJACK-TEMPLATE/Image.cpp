#include "pch.h"
#include "Image.h"
#include "Renderer.h"
#include "ResourceManager.h"

Image::Image(std::string goID, std::string f, float x, float y, bool v, double a, SDL_RendererFlip o) : 
	filename(f), position{ x, y }, visible(v), angle(a), orientation(o)
{
	id = goID;

    LOG_INFO("Creating image ", id, "...");

	texture = ResourceManager::addTexture(filename);
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Image::Image(std::string goID, std::string f, float x, float y, int w, int h, bool v, double a, SDL_RendererFlip o) :
    filename(f), position{ x, y }, width(w), height(h), visible(v), angle(a), orientation(o)
{
    id = goID;

    LOG_INFO("Creating image ", id, "...");

    texture = ResourceManager::addTexture(filename);
}

Image::~Image()
{ 
    LOG_INFO("Removing image ", id, "...");
}

void Image::update(float delta)
{ }

void Image::render() 
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