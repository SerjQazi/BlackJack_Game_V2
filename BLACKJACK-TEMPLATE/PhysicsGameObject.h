#pragma once

#include "GameObject.h"

class PhysicsGameObject : public GameObject
{
public:
	virtual void update(float delta) = 0;
	virtual void render() = 0;
	
	b2Body* getPhysicsBody()
	{
		return body;
	}

protected:
	PhysicsGameObject() : GameObject(), body(nullptr), bodyDef(nullptr) { }
	virtual ~PhysicsGameObject() { }

	b2Body* body;
	b2BodyDef* bodyDef;
};