#include "pch.h"
#include "Font.h"
#include "ResourceManager.h"

Font::Font(std::string f, int s, SDL_Color c) : filename(f), size(s), color(c), font(nullptr)
{ 
    font = ResourceManager::getInstance()->addFont(filename, size);
    if (font == nullptr)
    {
        LOG_ERROR("Error: Failed to load font...");
    }
}

Font::~Font()
{ }

void Font::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    color = { r, g, b, a };
}

std::string Font::getFilename() const
{
    return filename;
}

int Font::getSize() const
{
    return size;
}

SDL_Color Font::getColor() const
{
    return color;
}

TTF_Font* Font::getSDLFont() const
{
    return font;
}