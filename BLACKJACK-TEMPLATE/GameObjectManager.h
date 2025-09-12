#pragma once

#include "GameObject.h"
#include "GameConfiguration.h"
#include "PhysicsGameObject.h"

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	static void removeInstance();

	void addGameObject(GameObject* go, int depth = 0);

	GameObject* findGameObject(std::string goID);

	void removeGameObject(GameObject* go);
	void removeGameObject(std::string goID);
	void removeAllGameObjects();

	void deletePhysicsGameObjects();

	std::vector<GameObject*> getGameObjects();

private:
	GameObjectManager();
	~GameObjectManager();

	std::unordered_map<std::string, GameObject*> registry;
	std::multimap<int, GameObject*> gameObjects;
	std::vector<GameObject*> physicsGameObjects;

	static GameObjectManager* instance;
};