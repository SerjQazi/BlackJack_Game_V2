#pragma once

#include "PhysicsGameObject.h"
#include "World.h"

class Renderer;
class SceneManager;
class StaticSprite;

class StaticBody : public PhysicsGameObject
{
	friend class StaticSprite;

public:
	StaticBody(std::string goID, float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float angle = 0.0f, float density = 0.0f, float friction = 0.0f, float restitution = 0.0f);

	void update(float delta);
	void render();
	
	void setCamera(Camera* c);
	void setPosition(float x, float y);

	glm::vec2 position;
	float width;
	float height;
	float angle;

protected:
	~StaticBody();
};