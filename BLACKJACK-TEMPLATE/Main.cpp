#include "pch.h"

#include "Game.h"
#include "LevelScene.h"
#include "MenuScene.h"

int main(int argc, char* argv[])
{
    Game* game = Game::getInstance("config/config.json");

    //game->createScene<LevelScene>("level1");
    game->createScene<MenuScene>("menu");

    game->start();

    game->shutdown();

    return 0;
}