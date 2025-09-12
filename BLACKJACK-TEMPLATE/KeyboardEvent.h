#pragma once

#include "Event.h"
#include "Key.h"

class KeyboardEvent : public Event
{
public:
	KeyboardEvent(const std::string& type, const SDL_Event& sdlEvent);

	Uint32 getSDLType() const;
	Uint32 getTimestamp() const;
	Uint32 getState() const;
	Uint8 getRepeat() const;

	static const std::string KEYDOWN;
	static const std::string KEYUP;

	Key key;

private:
	Uint32 sdlType;
	Uint32 timestamp;
	Uint32 state;
	Uint8 repeat;	
};