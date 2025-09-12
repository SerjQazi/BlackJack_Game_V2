#pragma once

#include "GameObject.h"
#include "Button.h"
#include "UserEvent.h"
#include "EventRegistry.h"

class Chip : public GameObject
{
public:
	Chip(std::string goID, std::string filename, float x, float y, int rows, int cols, int value = 1);
	~Chip();

	void update(float delta);
	void render();

	void setFrame(int v);
	int getValue() const;

	void onButtonDown(const UserEvent& e);
	void onButtonUp(const UserEvent& e);

private:
	int value;
	Button* chip;
	Button* left;
	Button* right;
};