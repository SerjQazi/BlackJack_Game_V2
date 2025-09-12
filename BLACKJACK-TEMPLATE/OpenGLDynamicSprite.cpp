#include "pch.h"
#include "OpenGLDynamicSprite.h"
#include "SceneManager.h"

OpenGLDynamicSprite::OpenGLDynamicSprite(std::string goID, std::string filename, float x, float y, float width, float height, std::string vertexFilename, std::string fragFilename, bool rot, double a, float density, float friction, float restitution, bool flip)
    : OpenGLSprite(goID, filename, x, y, width, height, vertexFilename, fragFilename, flip)
{
    id = goID;

    world = SceneManager::getInstance()->currentWorld;

    dynamicBody = new DynamicBody(goID, x, y, static_cast<float>(width), static_cast<float>(height), static_cast<float>(a), density, friction, restitution);
    dynamicBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating dynamic sprite ", id, "...");
}

OpenGLDynamicSprite::OpenGLDynamicSprite(std::string goID, std::string filename, float x, float y, std::string vertexFilename, std::string fragFilename, bool rot, double a, float density, float friction, float restitution, bool flip)
    : OpenGLSprite(goID, filename, x, y, vertexFilename, fragFilename, flip)
{
    id = goID;

    world = SceneManager::getInstance()->currentWorld;

    dynamicBody = new DynamicBody(goID, position.x, position.y, static_cast<float>(frameWidth), static_cast<float>(frameHeight), static_cast<float>(a), density, friction, restitution);
    dynamicBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating dynamic sprite ", id, "...");
}

OpenGLDynamicSprite::~OpenGLDynamicSprite()
{
    LOG_INFO("Removing dynamic sprite ", id, "...");
    delete dynamicBody;
}

void OpenGLDynamicSprite::update(float delta)
{
    dynamicBody->update(delta);
    b2Vec2 bodyPosition = dynamicBody->getPhysicsBody()->GetPosition();
    position.x = (bodyPosition.x * world->scale - static_cast<float>(frameWidth) / 2.0f);
    position.y = (bodyPosition.y * world->scale - static_cast<float>(frameHeight) / 2.0f);
    OpenGLSprite::update(delta);
}

void OpenGLDynamicSprite::render()
{
    OpenGLSprite::render();
}

DynamicBody* OpenGLDynamicSprite::getBody()
{
    return dynamicBody;
}