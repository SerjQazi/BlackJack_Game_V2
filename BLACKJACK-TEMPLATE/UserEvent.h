#pragma once

#include "Event.h"

class UserEvent : public Event
{
public:
	UserEvent(const std::string& type, const SDL_Event& sdlEvent);

	virtual Uint32 getSDLType() const;
	virtual Uint32 getTimestamp() const;
	virtual Uint32 getState() const;
	virtual void* getData1() const;
	virtual void* getData2() const;

protected:
	Uint32 sdlType;
	Uint32 timestamp;
	Sint32 state;
	void* data1;
	void* data2;
};