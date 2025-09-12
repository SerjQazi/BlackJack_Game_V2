#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(std::string goID, float x, float y, int w, int h, SDL_Color c) : position{x, y}, width(w), height(h), color(c)
{
    id = goID;
    LOG_INFO("Creating rectangle ", id, "...");
}

Rectangle::Rectangle(std::string goID, glm::vec2 p, int w, int h, SDL_Color c) : position(p), width(w), height(h), color(c)
{
    id = goID;
    LOG_INFO("Creating rectangle ", id, "...");
}

Rectangle::~Rectangle()
{
    LOG_INFO("Removing rectangle ", id, "...");
}

void Rectangle::update(float delta)
{

}

void Rectangle::render()
{
    if (camera)
    {
        int screenX = static_cast<int>((position.x - camera->getViewPort().x) * camera->getZoom());
        int screenY = static_cast<int>((position.y - camera->getViewPort().y) * camera->getZoom());

        int transformedWidth = static_cast<int>(width * camera->getZoom());
        int transformedHeight = static_cast<int>(height * camera->getZoom());

        SDL_Rect dest = { screenX, screenY, transformedWidth, transformedHeight };
        SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(Renderer::getSDLRenderer(), &dest);
    }
    else
    {
        SDL_Rect fillRect = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
        SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(Renderer::getSDLRenderer(), &fillRect);
    }
}