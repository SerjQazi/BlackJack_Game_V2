#pragma once

class Frame
{
public:
    Frame() : id(""), source({ 0, 0, 0, 0 }) { }
    Frame(std::string id, SDL_Rect source) : id(id), source(source) { }

    std::string id;
    SDL_Rect source;
};