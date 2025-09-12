#include "pch.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{ 
	LOG_INFO("Initializing game object manager...");
}

GameObjectManager::~GameObjectManager()
{
	removeAllGameObjects();
}

GameObjectManager* GameObjectManager::getInstance()
{
	if (instance == nullptr)
		instance = new GameObjectManager();
	return instance;
}

void GameObjectManager::removeInstance()
{
	if (instance)
		delete instance;
}

void GameObjectManager::addGameObject(GameObject* go, int depth)
{
	LOG_INFO("Adding game object ", go->getObjectID(), "...");
	registry[go->getObjectID()] = go;
	gameObjects.insert(std::make_pair(depth, go));
}

GameObject* GameObjectManager::findGameObject(std::string goID)
{
	return registry[goID];
}

void GameObjectManager::removeGameObject(GameObject* go)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (it->second == go)
		{
			LOG_INFO("Removing game object ", go->getObjectID(), "...");
			registry.erase(go->getObjectID());
			gameObjects.erase(it);
			if(go->getWorld())
				physicsGameObjects.push_back(go);
			break;
		}
	}
}

void GameObjectManager::removeGameObject(std::string goID)
{
	GameObject* go = registry[goID];
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (it->second == go)
		{
			LOG_INFO("Removing game object ", go->getObjectID(), "...");
			registry.erase(go->getObjectID());
			gameObjects.erase(it);
			if (go->getWorld())
				physicsGameObjects.push_back(go);
			break;
		}
	}
}

void GameObjectManager::removeAllGameObjects()
{
	for (auto& pair : registry)
	{
		LOG_INFO("Removing game object ", pair.second->getObjectID(), "...");
		delete pair.second;
	}
	registry.clear();
	gameObjects.clear();

	for (auto& item : physicsGameObjects)
		delete item;
	physicsGameObjects.clear();
}

void GameObjectManager::deletePhysicsGameObjects()
{
	for (auto go : physicsGameObjects)
	{
		LOG_INFO("Removing game object ", go->getObjectID(), "...");
		delete go;
		go = nullptr;
	}
	physicsGameObjects.clear();
}

std::vector<GameObject*> GameObjectManager::getGameObjects()
{
	std::vector<GameObject*> sortedGameObject;
	for (const auto& pair : gameObjects) 
		sortedGameObject.push_back(pair.second);
	return sortedGameObject;
}

GameObjectManager* GameObjectManager::instance = nullptr;