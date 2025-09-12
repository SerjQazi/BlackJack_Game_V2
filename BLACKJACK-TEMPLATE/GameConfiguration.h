#pragma once

#include "Configuration.h"

class GameConfiguration : public Configuration
{
public:
    GameConfiguration();

    float x;
    float y;
    std::string windowTitle;
    std::string gameloop;
    std::string renderer;
    bool fullscreen;
    float zoom;
    int worldWidth;
    int worldHeight;
    bool physics;
    glm::vec2 gravity;
    float scale;
    int velocityIterations;
    int positionIterations;

    static bool debug;
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
};