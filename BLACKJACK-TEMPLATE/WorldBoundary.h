#pragma once

class WorldBoundary
{
public:
	WorldBoundary(float windowWidth, float windowHeight, float scale, b2World* world);
	~WorldBoundary();
};