#include "pch.h"
#include "DynamicSprite.h"
#include "SceneManager.h"
#include "Renderer.h"

DynamicSprite::DynamicSprite(std::string goID, std::string filename, float x, float y, int r, int c, int oX, int oY, bool v, bool rot, double a, float density, float friction, float restitution, SDL_RendererFlip o)
    : Sprite(goID, filename, x, y, r, c, oX, oY, v, a, o)
{
    id = goID;

    world = SceneManager::getInstance()->currentWorld; 

    dynamicBody = new DynamicBody(goID, x, y, static_cast<float>(width), static_cast<float>(height), static_cast<float>(angle), density, friction, restitution);
    dynamicBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating dynamic sprite ", id, "...");
}

DynamicSprite::DynamicSprite(std::string goID, std::string filename, float x, float y, bool v, bool rot, double a, float density, float friction, float restitution, SDL_RendererFlip o)
    : Sprite(goID, filename, x, y, v, a, o)
{
    id = goID;

    world = SceneManager::getInstance()->currentWorld;

    dynamicBody = new DynamicBody(goID, x, y, static_cast<float>(width), static_cast<float>(height), static_cast<float>(angle), density, friction, restitution);
    dynamicBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating dynamic sprite ", id, "...");
}

DynamicSprite::~DynamicSprite()
{
    LOG_INFO("Removing dynamic sprite ", id, "...");
    delete dynamicBody;
}

void DynamicSprite::update(float delta)
{
    Sprite::update(delta);
    dynamicBody->update(delta);
    b2Vec2 bodyPosition = dynamicBody->getPhysicsBody()->GetPosition();
    position = { (bodyPosition.x * world->scale - static_cast<float>(width) / 2.0f), (bodyPosition.y * world->scale - static_cast<float>(height) / 2.0f) };
}

void DynamicSprite::render()
{
    Sprite::render();
}

void DynamicSprite::setCamera(Camera* c)
{
    float zoom = c->getZoom();

    position.x *= zoom;
    position.y *= zoom;

    width *= static_cast<int>(zoom);
    height *= static_cast<int>(zoom);

    b2Vec2 bodyPosition = { position.x / world->scale, position.y / world->scale };

    b2PolygonShape box;
    box.SetAsBox((width / world->scale) / 2.0f, (height / world->scale) / 2.0f);

    b2Fixture* oldFixture = dynamicBody->getPhysicsBody()->GetFixtureList();
    if (oldFixture)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = oldFixture->GetDensity();
        fixtureDef.friction = oldFixture->GetFriction();
        fixtureDef.restitution = oldFixture->GetRestitution();

        while (oldFixture)
        {
            b2Fixture* next = oldFixture->GetNext();
            dynamicBody->getPhysicsBody()->DestroyFixture(oldFixture);
            oldFixture = next;
        }

        dynamicBody->getPhysicsBody()->CreateFixture(&fixtureDef);
    }

    dynamicBody->getPhysicsBody()->SetTransform(bodyPosition, dynamicBody->getPhysicsBody()->GetAngle());

    position = { bodyPosition.x * world->scale - width / 2.0f,
                 bodyPosition.y * world->scale - height / 2.0f };
}

DynamicBody* DynamicSprite::getBody()
{
    return dynamicBody;
}