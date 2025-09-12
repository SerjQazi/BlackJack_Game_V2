#include "pch.h"
#include "StaticSprite.h"
#include "SceneManager.h"
#include "Renderer.h"

StaticSprite::StaticSprite(std::string goID, std::string filename, float x, float y, int r, int c, int oX, int oY, bool v, bool rot, double a, float density, float friction, float restitution, SDL_RendererFlip o)
    : Sprite(goID, filename, x, y, r, c, oX, oY, v, a, o)
{
    world = SceneManager::getInstance()->currentWorld;

    staticBody = new StaticBody(goID, x, y, static_cast<float>(width), static_cast<float>(height), static_cast<float>(angle), density, friction, restitution);
    staticBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating static sprite ", id, "...");
}

StaticSprite::StaticSprite(std::string goID, std::string filename, float x, float y, bool v, bool rot, double a, float density, float friction, float restitution, SDL_RendererFlip o)
    : Sprite(goID, filename, x, y, v, a, o)
{
    world = SceneManager::getInstance()->currentWorld;

    staticBody = new StaticBody(goID, x, y, static_cast<float>(width), static_cast<float>(height), static_cast<float>(angle), density, friction, restitution);
    staticBody->getPhysicsBody()->SetFixedRotation(rot);

    LOG_INFO("Creating static sprite ", id, "...");
}

StaticSprite::~StaticSprite()
{
    LOG_INFO("Removing static sprite ", id, "...");
    delete staticBody;
}

void StaticSprite::update(float delta)
{
    Sprite::update(delta);
    staticBody->update(delta);
    b2Vec2 bodyPosition = staticBody->getPhysicsBody()->GetPosition();
    position = { (bodyPosition.x * world->scale - static_cast<float>(width) / 2.0f), (bodyPosition.y * world->scale - static_cast<float>(height) / 2.0f) };
}

void StaticSprite::render()
{
    Sprite::render();
}

void StaticSprite::setCamera(Camera* c)
{
    float zoom = c->getZoom();

    position.x *= zoom;
    position.y *= zoom;

    width *= static_cast<int>(zoom);
    height *= static_cast<int>(zoom);

    b2Vec2 bodyPosition = { position.x / world->scale, position.y / world->scale };

    b2PolygonShape box;
    box.SetAsBox((width / world->scale) / 2.0f, (height / world->scale) / 2.0f);

    b2Fixture* oldFixture = staticBody->getPhysicsBody()->GetFixtureList();
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
            staticBody->getPhysicsBody()->DestroyFixture(oldFixture);
            oldFixture = next;
        }

        staticBody->getPhysicsBody()->CreateFixture(&fixtureDef);
    }

    staticBody->getPhysicsBody()->SetTransform(bodyPosition, staticBody->getPhysicsBody()->GetAngle());

    position = { bodyPosition.x * world->scale - width / 2.0f,
                 bodyPosition.y * world->scale - height / 2.0f };
}

StaticBody* StaticSprite::getBody()
{
    return staticBody;
}