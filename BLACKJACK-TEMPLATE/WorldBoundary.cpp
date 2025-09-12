#include "pch.h"
#include "WorldBoundary.h"

WorldBoundary::WorldBoundary(float windowWidth, float windowHeight, float scale, b2World* world)
{
    LOG_INFO("Creating world boundaries...");

    b2BodyDef topBodyDef;
    topBodyDef.position.Set(windowWidth / 2.0f / scale, -1.0f / scale);
    b2Body* topBody = world->CreateBody(&topBodyDef);
    b2PolygonShape topBox;
    topBox.SetAsBox(windowWidth / 2.0f / scale, 1.0f / scale);
    b2FixtureDef topFixtureDef;
    topFixtureDef.shape = &topBox;
    topFixtureDef.restitution = 0.0f;
    topBody->CreateFixture(&topFixtureDef);
    topBody->GetUserData().pointer = reinterpret_cast<uintptr_t>("top");

    b2BodyDef leftBodyDef;
    leftBodyDef.position.Set(-1.0f / scale, windowHeight / 2.0f / scale);
    b2Body* leftBody = world->CreateBody(&leftBodyDef);
    b2PolygonShape leftBox;
    leftBox.SetAsBox(1.0f / scale, windowHeight / 2.0f / scale);
    b2FixtureDef leftFixtureDef;
    leftFixtureDef.shape = &leftBox;
    leftFixtureDef.restitution = 0.0f;
    leftBody->CreateFixture(&leftFixtureDef);
    leftBody->GetUserData().pointer = reinterpret_cast<uintptr_t>("left");

    b2BodyDef rightBodyDef;
    rightBodyDef.position.Set(windowWidth / scale + 1.0f / scale, windowHeight / 2.0f / scale);
    b2Body* rightBody = world->CreateBody(&rightBodyDef);
    b2PolygonShape rightBox;
    rightBox.SetAsBox(1.0f / scale, windowHeight / 2.0f / scale);
    b2FixtureDef rightFixtureDef;
    rightFixtureDef.shape = &rightBox;
    rightFixtureDef.restitution = 0.0f;
    rightBody->CreateFixture(&rightFixtureDef);
    rightBody->GetUserData().pointer = reinterpret_cast<uintptr_t>("right");

    b2BodyDef bottomBodyDef;
    bottomBodyDef.position.Set(windowWidth / 2.0f / scale, windowHeight / scale + 1.0f / scale);
    b2Body* bottomBody = world->CreateBody(&bottomBodyDef);
    b2PolygonShape bottomBox;
    bottomBox.SetAsBox(windowWidth / 2.0f / scale, 1.0f / scale);
    b2FixtureDef bottomFixtureDef;
    bottomFixtureDef.shape = &bottomBox;
    bottomFixtureDef.restitution = 0.0f;
    bottomBody->CreateFixture(&bottomFixtureDef);
    bottomBody->GetUserData().pointer = reinterpret_cast<uintptr_t>("bottom");
}

WorldBoundary::~WorldBoundary()
{ }