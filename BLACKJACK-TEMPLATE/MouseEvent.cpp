#include "pch.h"
#include "MouseEvent.h"

MouseEvent::MouseEvent(const std::string& type, const SDL_Event& sdlEvent) : 
	Event(type, sdlEvent), position({ static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y) })
{
    sdlType = sdlEvent.type;
    timestamp = (sdlEvent.type == SDL_MOUSEMOTION) ? sdlEvent.motion.timestamp : sdlEvent.button.timestamp;
    button = (sdlEvent.type == SDL_MOUSEMOTION) ? 0 : sdlEvent.button.button;
    buttonState = (sdlEvent.type == SDL_MOUSEMOTION) ? sdlEvent.motion.state : sdlEvent.button.state;
    numClicks = (sdlEvent.type == SDL_MOUSEMOTION) ? 0 : sdlEvent.button.clicks;
}


Uint32 MouseEvent::getTimestamp() const
{
	return timestamp;
}

Uint32 MouseEvent::getButton() const
{
	return button;
}

Uint32 MouseEvent::getButtonState() const
{
	return buttonState;
}

Uint8 MouseEvent::getNumClicks() const
{
	return numClicks;
}

const std::string MouseEvent::MOUSEDOWN = "mousedown";
const std::string MouseEvent::MOUSEUP = "mouseup";
const std::string MouseEvent::MOUSEMOVE = "mousemove";

const Uint32 MouseEvent::MOUSELEFT = SDL_BUTTON_LEFT;
const Uint32 MouseEvent::MOUSEMIDDLE = SDL_BUTTON_MIDDLE;
const Uint32 MouseEvent::MOUSERIGHT = SDL_BUTTON_RIGHT;