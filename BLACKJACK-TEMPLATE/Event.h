#pragma once

class Event
{
public:
    Event(const std::string& type, const SDL_Event& sdlEvent) : type(type), sdlEvent(sdlEvent) 
    { }

    virtual ~Event() = default;

    std::string getType() const 
    { 
        return type; 
    }

    SDL_Event getSDLEvent() const 
    { 
        return sdlEvent; 
    }

private:
    std::string type;
    SDL_Event sdlEvent;
};