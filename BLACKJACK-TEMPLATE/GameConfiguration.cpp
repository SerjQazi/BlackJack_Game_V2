#include "pch.h"
#include "GameConfiguration.h"

GameConfiguration::GameConfiguration()
    : x(0.0f), y(0.0f), windowTitle("TITLE"), gameloop("hybrid"), renderer("direct3d"), fullscreen(false), zoom(1.0f), worldWidth(0), worldHeight(0), physics(false), gravity({ 0.0f, 0.0f }), scale(30.0f), velocityIterations(6), positionIterations(2)
{ }

bool GameConfiguration::debug = false;
int GameConfiguration::SCREEN_WIDTH = 0;
int GameConfiguration::SCREEN_HEIGHT = 0;