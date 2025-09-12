#include "pch.h"
#include "World.h"
#include "GameObject.h"
#include "PhysicsGameObject.h"
#include "Renderer.h"

World::World(float windowWidth, float windowHeight, float s, glm::vec2 gravity) : debug(nullptr)
{ 
    scale = s;
    world = new b2World({ gravity.x, gravity.y });
    LOG_INFO("Physics world created...");

    if (GameConfiguration::debug)
    {
        debug = new RenderDebug();
        debug->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
        world->SetDebugDraw(debug);
        LOG_INFO("Physics debug enabled...");
    }

    WorldBoundary boundary(windowWidth, windowHeight, scale, world);
}

World::~World()
{
    world->SetContactListener(nullptr);

    for (b2Body* body = world->GetBodyList(); body != nullptr; )
    {
        b2Body* nextBody = body->GetNext();
        world->DestroyBody(body);
        body = nextBody;
    }

    if (world && debug) 
    {
        world->SetDebugDraw(nullptr);
        delete debug;
        debug = nullptr;
    }

    delete world;
    
    LOG_INFO("Removing world...");
}

void World::addBody(GameObject* go)
{
    world->SetContactListener(go);
}

void World::removeBody(GameObject* go)
{
    if(auto pgo = dynamic_cast<PhysicsGameObject*>(go))
        world->DestroyBody(pgo->getPhysicsBody());
}

b2World* World::getPhysicsWorld()
{
    return world;
}

void World::renderDebug()
{
    world->DebugDraw();
}

float World::scale = 1.0f;