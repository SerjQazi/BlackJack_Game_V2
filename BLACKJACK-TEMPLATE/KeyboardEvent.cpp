#include "pch.h"
#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(const std::string& type, const SDL_Event& sdlEvent) : Event(type, sdlEvent)
{ 
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
	{
		sdlType = sdlEvent.type;
		timestamp = sdlEvent.key.timestamp;
		state = sdlEvent.key.state;
		key = Key(sdlEvent.key.keysym.scancode);
		key.sym = sdlEvent.key.keysym.sym;
	}
}

Uint32 KeyboardEvent::getSDLType() const
{
	return sdlType;
}

Uint32 KeyboardEvent::getTimestamp() const
{
	return timestamp;
}

Uint32 KeyboardEvent::getState() const
{
	return state;
}

Uint8 KeyboardEvent::getRepeat() const
{
	return repeat;
}

const std::string KeyboardEvent::KEYDOWN = "keydown";
const std::string KeyboardEvent::KEYUP = "keyup";