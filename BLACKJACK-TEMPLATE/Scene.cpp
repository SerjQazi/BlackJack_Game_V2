#include "pch.h"
#include "Scene.h"
#include "Engine.h"
#include "GameObjectManager.h"

Scene::Scene(std::string goID, Camera* c, World* w)
{
    id = goID;
    camera = c;
    world = w;

    LOG_INFO("Scene ", id, " created...");
}

Scene::~Scene()
{
    LOG_INFO("Removing scene...");
    if (world)
    {
        world->getPhysicsWorld()->SetContactListener(nullptr);
        delete world;
    }
}

void Scene::update(float delta)
{
    GameObjectManager::getInstance()->deletePhysicsGameObjects();

    if (camera)
        camera->update(delta);
    
    if (world)
    {
        int32 velocityIterations = Engine::config->velocityIterations;
        int32 positionIterations = Engine::config->positionIterations;
        world->getPhysicsWorld()->Step(delta, velocityIterations, positionIterations);
    }

    std::vector<GameObject*> gameObjects = GameObjectManager::getInstance()->getGameObjects();
    for (auto item : gameObjects)
        item->update(delta);
}

void Scene::render()
{
    std::vector<GameObject*> gameObjects = GameObjectManager::getInstance()->getGameObjects();
    for (auto item : gameObjects)
        item->render();

    if (GameConfiguration::debug)
    {
        world->renderDebug();
    }
}

void Scene::addGameObject(GameObject* go, int depth)
{
    if (camera)
        go->setCamera(camera);

    if (world)
        go->setWorld(world);

    GameObjectManager::getInstance()->addGameObject(go, depth);
}

void Scene::removeGameObject(GameObject* go)
{
    GameObjectManager::getInstance()->removeGameObject(go);
}

void Scene::removeAllGameObjects()
{
    GameObjectManager::getInstance()->removeAllGameObjects();
}