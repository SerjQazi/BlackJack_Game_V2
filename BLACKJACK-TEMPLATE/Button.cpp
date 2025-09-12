#include "pch.h"
#include "Button.h"
#include "InputManager.h"

Button::Button(std::string goID, std::string filename, float x, float y, int rows, int cols) : pressed(false), released(false)
{
	id = goID;

	sprite = new Sprite(goID, filename, x, y, rows, cols);
	addEventListener(MouseEvent::MOUSEDOWN, this, &Button::onButtonDown);
	addEventListener(MouseEvent::MOUSEUP, this, &Button::onButtonUp);

	EventRegistry::getInstance()->registerEvent(Button::PRESSED);
	EventRegistry::getInstance()->registerEvent(Button::RELEASED);
}

Button::Button(std::string goID, std::string filename, float x, float y) : pressed(false), released(false)
{
	id = goID;

	sprite = new Sprite(goID, filename, x, y);
	addEventListener(MouseEvent::MOUSEDOWN, this, &Button::onButtonDown);
	addEventListener(MouseEvent::MOUSEUP, this, &Button::onButtonUp);

	EventRegistry::getInstance()->registerEvent(Button::PRESSED);
	EventRegistry::getInstance()->registerEvent(Button::RELEASED);
}

Button::~Button()
{
	removeEventListener(MouseEvent::MOUSEDOWN, this, &Button::onButtonDown);
	removeEventListener(MouseEvent::MOUSEUP, this, &Button::onButtonUp);
	delete sprite;
}

void Button::update(float delta)
{
	sprite->update(delta);

	if (pressed)
	{
		pressed = false;
		InputManager::pushUserEvent(Button::PRESSED, &id);
	}
	else if (released)
	{
		released = false;
		InputManager::pushUserEvent(Button::RELEASED, &id);
	}
}

void Button::render()
{
	sprite->render();
}

glm::vec2 Button::getPosition() const
{
	return sprite->position;
}

int Button::getWidth() const
{
	return sprite->width;
}

int Button::getHeight() const
{
	return sprite->height;
}

void Button::addFrame(const std::string& name, const int startIndex, int width, int height, int rows, int cols)
{
	sprite->addAnimation(name, startIndex, 1, width, height, rows, cols);
	sprite->play(name, 1);
}

void Button::setFrame(const std::string& name)
{
	sprite->play(name, 1);
}

bool Button::isVisible()
{
	return sprite->visible;
}

void Button::setVisible(bool v)
{
	sprite->visible = v;
}

void Button::onButtonDown(const MouseEvent& e)
{
	if (e.position.x >= sprite->position.x && e.position.x <= sprite->position.x + sprite->width &&
		e.position.y >= sprite->position.y && e.position.y <= sprite->position.y + sprite->height && sprite->visible)
	{
		pressed = true;
	}
}

void Button::onButtonUp(const MouseEvent& e)
{
	if (e.position.x >= sprite->position.x && e.position.x <= sprite->position.x + sprite->width &&
		e.position.y >= sprite->position.y && e.position.y <= sprite->position.y + sprite->height && sprite->visible)
	{
		released = true;
	}
}

const std::string Button::PRESSED = "pressed";
const std::string Button::RELEASED = "released";