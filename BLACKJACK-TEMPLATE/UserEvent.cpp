#include "pch.h"
#include "UserEvent.h"

UserEvent::UserEvent(const std::string& type, const SDL_Event& sdlEvent) : Event(type, sdlEvent)
{
	if (sdlEvent.type == SDL_USEREVENT)
	{
		sdlType = sdlEvent.type;
		timestamp = sdlEvent.user.timestamp;
		state = sdlEvent.user.code;
		data1 = (void*)sdlEvent.user.data1;
		data2 = (void*)sdlEvent.user.data2;
	}
}

Uint32 UserEvent::getSDLType() const
{
	return sdlType;
}

Uint32 UserEvent::getTimestamp() const
{
	return timestamp;
}

Uint32 UserEvent::getState() const
{
	return state;
}

void* UserEvent::getData1() const
{
	return data1;
}

void* UserEvent::getData2() const
{
	return data2;
}