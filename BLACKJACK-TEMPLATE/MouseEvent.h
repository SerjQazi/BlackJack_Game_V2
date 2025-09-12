#pragma once

#include "Event.h"

class MouseEvent : public Event
{
public:
	MouseEvent(const std::string& type, const SDL_Event& sdlEvent);

	Uint32 getTimestamp() const;
	Uint32 getButton() const;
	Uint32 getButtonState() const;
	Uint8 getNumClicks() const;

	static const std::string MOUSEDOWN;
	static const std::string MOUSEUP;
	static const std::string MOUSEMOVE;

	static const Uint32 MOUSELEFT;
	static const Uint32 MOUSEMIDDLE;
	static const Uint32 MOUSERIGHT;

	glm::vec2 position;

private:
	Uint32 sdlType;
	Uint32 timestamp;
	Uint32 button;
	Uint32 buttonState;
	Uint8 numClicks;
};