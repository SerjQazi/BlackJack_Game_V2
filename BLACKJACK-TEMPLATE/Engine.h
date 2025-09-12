#pragma once

#include "Window.h"
#include "SceneManager.h"
#include "GameConfiguration.h"
#include "World.h"

class Camera;
class Renderer;
class Game;
class Gameloop;
class ConsoleLogger;
class InputManager;
class ResourceManager;
class AnimationManager;
class TimerManager;
class ConfigurationManager;
class GameObjectManager;
class Scene;

class Engine
{
public:
	Engine(const std::string& filename);
	~Engine();

	void start();
	void stop();
	void pause();
	void resume();
	void shutdown();

	void process();

	bool isRunning();
	bool isPaused();

	template <typename T>
	T* createScene(std::string goID)
	{
		World* world = nullptr;
		if (config->physics)
			world = new World(static_cast<float>(config->SCREEN_WIDTH), static_cast<float>(config->SCREEN_HEIGHT), config->scale, { config->gravity.x, config->gravity.y });

		return SceneManager::getInstance()->createScene<T>(goID, window->getCamera(), world);
	}
	void addScene(Scene* scene);
	void removeScene();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	Camera* getCamera();

	static GameConfiguration* config;

private:
	Gameloop* gameloop;
	Window* window;	
};