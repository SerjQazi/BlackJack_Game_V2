#include "pch.h"
#include "Engine.h"
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"
#include "FrameGameloop.h"
#include "FixedGameloop.h"
#include "VariableGameloop.h"
#include "HybridGameloop.h"
#include "ConsoleLogger.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "TimerManager.h"
#include "ConfigurationManager.h"
#include "GameObjectManager.h"

Engine::Engine(const std::string& filename) : gameloop(nullptr)
{
	srand(static_cast<unsigned int>(time(0)));

	ConsoleLogger* consoleLogger = new ConsoleLogger();
	LoggerManager::getInstance()->setLogger(consoleLogger);

	LOG_INFO("Initializing game engine...");

	config = new GameConfiguration();
	ConfigurationManager::getInstance()->loadConfiguration(filename, config);
	window = new Window(*config);

	GameObjectManager::getInstance();
	SceneManager::getInstance();
	InputManager::getInstance();
	ResourceManager::getInstance();
	AnimationManager::getInstance();
	TimerManager::getInstance();

	if (config->gameloop == "hybrid")
		gameloop = new HybridGameloop();
	else if (config->gameloop == "variable")
		gameloop = new VariableGameloop();
	else if (config->gameloop == "fixed")
		gameloop = new FixedGameloop();
	else if (config->gameloop == "frame")
		gameloop = new FrameGameloop();
	else
	{
		LOG_ERROR("Error: Cannot start game loop...");
		SDL_Quit();
	}

	LOG_INFO("Game engine started...");
}

Engine::~Engine()
{
	ConfigurationManager::removeInstance();
	GameObjectManager::removeInstance();
	TimerManager::removeInstance();
	AnimationManager::removeInstance();
	ResourceManager::removeInstance();
	SceneManager::removeInstance();
	InputManager::removeInstance();
	Renderer::removeInstance();
	
	delete gameloop;
	delete window;
}

void Engine::process()
{
	gameloop->process();
}

void Engine::start()
{
	gameloop->running = true;
	gameloop->paused = false;

	SceneManager::getInstance()->gameScenes.back()->onEnter();

	process();
}

void Engine::stop()
{
	gameloop->running = false;
}

void Engine::pause()
{
	gameloop->paused = true;
}

void Engine::resume()
{
	gameloop->paused = false;
}

void Engine::shutdown()
{
	if (isRunning())
		stop();
}

bool Engine::isRunning()
{
	return gameloop->running;
}

bool Engine::isPaused()
{
	return gameloop->paused;
}

void Engine::addScene(Scene* scene)
{
	World* world = nullptr;
	if (config->physics)
		world = new World(static_cast<float>(config->SCREEN_WIDTH), static_cast<float>(config->SCREEN_HEIGHT), config->scale, { config->gravity.x, config->gravity.y });

	SceneManager::getInstance()->addScene(scene, window->getCamera(), world);
}

void Engine::removeScene()
{
	SceneManager::getInstance()->removeScene();
}

SDL_Window* Engine::getWindow()
{
	return Window::getSDLWindow();
}

SDL_Renderer* Engine::getRenderer()
{
	return Renderer::getSDLRenderer();
}

Camera* Engine::getCamera()
{
	return window->getCamera();
}

GameConfiguration* Engine::config = nullptr;