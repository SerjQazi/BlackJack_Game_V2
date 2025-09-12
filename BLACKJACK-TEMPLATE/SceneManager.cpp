#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{ 
	LOG_INFO("Initializing scene manager...");
}

SceneManager::~SceneManager()
{
	for (auto item : gameScenes)
	{
		item->onExit();
		delete item;
	}

	gameScenes.clear();
}

SceneManager* SceneManager::getInstance()
{
	if (instance == nullptr)
		instance = new SceneManager();
	return instance;
}

void SceneManager::removeInstance()
{
	if (instance)
		delete instance;
}

void SceneManager::addScene(Scene* scene, Camera* c, World* w)
{
	if (c)
	{
		currentCamera = c;
		scene->setCamera(c);
	}

	if (w)
	{
		currentWorld = w;
		scene->setWorld(w);
	}

	gameScenes.push_back(scene);
}

void SceneManager::removeScene()
{
	if (!gameScenes.empty())
	{
		gameScenes.back()->onExit();
		delete gameScenes.back();
		gameScenes.erase(gameScenes.end() - 1);
		if (!gameScenes.empty())
		{
			currentCamera = gameScenes.back()->getCamera();
			currentWorld = gameScenes.back()->getWorld();
			gameScenes.back()->onEnter();
		}
	}
}

void SceneManager::update(float delta)
{
	if (!gameScenes.empty())
		gameScenes.back()->update(delta);
}

void SceneManager::render()
{
	if (!gameScenes.empty())
		gameScenes.back()->render();
}

Camera* SceneManager::currentCamera = nullptr;
World* SceneManager::currentWorld = nullptr;
SceneManager* SceneManager::instance = nullptr;