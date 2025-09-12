#pragma once

#include "Scene.h"
#include "Engine.h"

class Game
{
public:
	~Game();

	static Game* getInstance(const std::string& filename);
	static void removeInstance();

	static void start();
	static void stop();
	static void pause();
	static void resume();
	static void shutdown();

	bool isRunning();
	bool isPaused();

	template <typename T>
	T* createScene(std::string goID)
	{
		return engine->createScene<T>(goID);
	}
	void addScene(Scene* scene);
	void removeScene();

private:
	Game(const std::string& filename);
	
	static Engine* engine;
	static Game* instance;
};