#pragma once

#include "Gameloop.h"
#include "GameObject.h"
#include "PhysicsGameObject.h"
#include "Camera.h"
#include "World.h"

class Engine;
class GameObjectManager;

class Scene : public GameObject
{
public:
	Scene(std::string goID, Camera* c = nullptr, World* w = nullptr);
	virtual ~Scene();

	virtual void update(float delta);
	virtual void render();

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	void addGameObject(GameObject* go, int depth);
	void removeGameObject(GameObject*);
	void removeAllGameObjects();
};