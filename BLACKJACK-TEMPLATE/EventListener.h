#pragma once

#include "InputManager.h"
#include "EventDispatcher.h"
#include "EventRegistry.h"
#include "CollisionEvent.h"

class EventListener : public b2ContactListener
{
public:
    EventListener() 
    {
        EventRegistry::getInstance()->registerEvent(CollisionEvent::COLLISIONBEGIN);
        EventRegistry::getInstance()->registerEvent(CollisionEvent::COLLISIONEND);
    }

    virtual ~EventListener() = default;

    template <typename T>
    void addEventListener(const std::string& eventType, T* instance, void (T::* method)(const Event&))
    {
        EventDispatcher::getInstance()->addEventListener(eventType, instance, method);
    }

    template <typename T, typename E>
    void addEventListener(const std::string& eventType, T* instance, void (T::* method)(const E&))
    {
        EventDispatcher::getInstance()->addEventListener(eventType, instance, method);
    }

    template <typename T>
    void removeEventListener(const std::string& eventType, T* instance, void (T::* method)(const Event&))
    {
        EventDispatcher::getInstance()->removeEventListener(eventType, instance, method);
    }

    template <typename T, typename E>
    void removeEventListener(const std::string& eventType, T* instance, void (T::* method)(const E&))
    {
        EventDispatcher::getInstance()->removeEventListener(eventType, instance, method);
    }

    virtual void BeginContact(b2Contact* contact) override
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        if(bodyA != nullptr && bodyB != nullptr)
            InputManager::pushUserEvent(CollisionEvent::COLLISIONBEGIN, bodyA, bodyB);
    }

    virtual void EndContact(b2Contact* contact) override
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        if (bodyA != nullptr && bodyB != nullptr)
            InputManager::pushUserEvent(CollisionEvent::COLLISIONEND, bodyA, bodyB);
    }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
    {
        
    }

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
    {

    }

private:
    std::unordered_set<b2Body*> ignoredBodies;
};