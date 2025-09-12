#pragma once

#include "UserEvent.h"

class CollisionEvent : public UserEvent
{
public:
	static const std::string COLLISIONBEGIN;
	static const std::string COLLISIONEND;
};