#pragma once

#include "Camera.h"
#include "World.h"
#include "EventListener.h"

class GameObjectManager;

class GameObject : public EventListener
{
	friend class GameObjectManager;

public:
	virtual void update(float delta) = 0;
	virtual void render() = 0; 

	virtual std::string getObjectID()
	{
		return id;
	}

	virtual void setCamera(Camera* c)
	{
		camera = c;
	}

	Camera* getCamera()
	{
		return camera;
	}

	void setWorld(World* w)
	{
		world = w;
	}

	World* getWorld()
	{
		return world;
	}

protected:
	GameObject() : world(nullptr), camera(nullptr) { }
	virtual ~GameObject() = default;
	std::string id;
	Camera* camera;
	World* world;
};