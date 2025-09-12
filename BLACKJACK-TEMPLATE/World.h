#pragma once

#include "WorldBoundary.h"
#include "RenderDebug.h"

class GameObject;
class PhysicsGameObject;
class Renderer;

class World
{
public:
    World(float windowWidth, float windowHeight, float scale, glm::vec2 gravity);
    virtual ~World();

    void addBody(GameObject* go);
    void removeBody(GameObject* go);

    b2World* getPhysicsWorld();

    void renderDebug();

    static float scale;

protected:
    b2World* world;
    RenderDebug* debug;
};