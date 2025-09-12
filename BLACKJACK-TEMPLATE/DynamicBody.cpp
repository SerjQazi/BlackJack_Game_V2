#include "pch.h"
#include "DynamicBody.h"
#include "Renderer.h"
#include "SceneManager.h"

DynamicBody::DynamicBody(std::string goID, float x, float y, float width, float height, float angle, float density, float friction, float restitution)
    : position({ x, y }), width(width), height(height), angle(angle)
{
    id = goID;

    world = SceneManager::getInstance()->currentWorld;

    if (world)
    {
        bodyDef = new b2BodyDef();
        bodyDef->type = b2_dynamicBody;
        bodyDef->position.Set((x + static_cast<float>(width) / 2.0f) / world->scale, (y + static_cast<float>(height) / 2.0f) / world->scale);
        bodyDef->angle = static_cast<float>(angle) * static_cast<float>(M_PI) / 180.0f;

        body = world->getPhysicsWorld()->CreateBody(bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(static_cast<float>(width) / (2.0f * world->scale), static_cast<float>(height) / (2.0f * world->scale));

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = density;
        fixtureDef.friction = friction; 
        fixtureDef.restitution = restitution;

        body->CreateFixture(&fixtureDef);

        body->GetUserData().pointer = reinterpret_cast<uintptr_t>(id.c_str());
    }

    LOG_INFO("Creating dynamic body ", id, "...");
}

DynamicBody::~DynamicBody()
{
    LOG_INFO("Removing dynamic body ", id, "...");
    world->removeBody(this);
    delete bodyDef;
    body = nullptr;
    bodyDef = nullptr;
}

void DynamicBody::update(float delta)
{
    position = { body->GetPosition().x * world->scale - static_cast<float>(width) / 2.0f, body->GetPosition().y * world->scale - static_cast<float>(height) / 2.0f };
    angle = body->GetAngle();
}

void DynamicBody::render()
{ }

void DynamicBody::setCamera(Camera* c)
{
    PhysicsGameObject::setCamera(c);

    float zoom = c->getZoom();
    float bodyWidth = (width * zoom) / world->scale;
    float bodyHeight = (height * zoom) / world->scale;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(bodyWidth / 2.0f, bodyHeight / 2.0f);

    b2Fixture* existingFixture = body->GetFixtureList();
    if (existingFixture)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = existingFixture->GetDensity();
        fixtureDef.friction = existingFixture->GetFriction();
        fixtureDef.restitution = existingFixture->GetRestitution();

        while (existingFixture)
        {
            b2Fixture* next = existingFixture->GetNext();
            body->DestroyFixture(existingFixture);
            existingFixture = next;
        }

        body->CreateFixture(&fixtureDef);
    }

    width *= zoom;
    height *= zoom;

    b2Vec2 bodyPosition = body->GetPosition();
    position = { bodyPosition.x * world->scale - static_cast<float>(bodyWidth) / 2.0f,
                 bodyPosition.y * world->scale - static_cast<float>(bodyHeight) / 2.0f };
}


void DynamicBody::setPosition(float x, float y)
{
    bodyDef->position.Set((x + static_cast<float>(width) / 2.0f) / world->scale, (y + static_cast<float>(height) / 2.0f) / world->scale);
    body->SetTransform(bodyDef->position, bodyDef->angle);

    position = { body->GetPosition().x * world->scale - static_cast<float>(width) / 2.0f, body->GetPosition().y * world->scale - static_cast<float>(height) / 2.0f };
}