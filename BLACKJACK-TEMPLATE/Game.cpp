#include "pch.h"
#include "Game.h"

Game::Game(const std::string& filename)
{
	engine = new Engine(filename);
}

Game::~Game()
{
	LOG_INFO("Shutting down game engine...");

	delete engine;

	SDL_Quit();
}

Game* Game::getInstance(const std::string& filename)
{
	if (instance == nullptr)
		instance = new Game(filename);

	return instance;
}

void Game::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void Game::start()
{
	engine->start();
}

void Game::stop()
{
	engine->stop();
}

void Game::pause()
{
	engine->pause();
}

void Game::resume()
{
	engine->resume();
}

void Game::shutdown()
{
	engine->shutdown();

	if (instance != nullptr)
		Game::removeInstance();
}

bool Game::isRunning()
{
	return engine->isRunning();
}

bool Game::isPaused()
{
	return engine->isPaused();
}

void Game::addScene(Scene* scene)
{
	engine->addScene(scene);
}

void Game::removeScene()
{
	engine->removeScene();
}

Engine* Game::engine = nullptr;
Game* Game::instance = nullptr;