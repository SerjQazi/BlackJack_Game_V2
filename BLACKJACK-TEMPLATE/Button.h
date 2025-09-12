#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "MouseEvent.h"
#include "EventRegistry.h"

class Button : public GameObject
{
public:
	Button(std::string goID, std::string filename, float x, float y, int rows, int cols);
	Button(std::string goID, std::string filename, float x, float y);
	~Button();

	void update(float delta);
	void render();

	glm::vec2 getPosition() const;
	int getWidth() const;
	int getHeight() const;

	void addFrame(const std::string& name, const int startIndex, int width, int height, int rows, int cols);
	void setFrame(const std::string& name);

	bool isVisible();
	void setVisible(bool v);

	void onButtonDown(const MouseEvent& e);
	void onButtonUp(const MouseEvent& e);

	static const std::string PRESSED;
	static const std::string RELEASED;

private:
	Sprite* sprite;
	bool pressed;
	bool released;
};