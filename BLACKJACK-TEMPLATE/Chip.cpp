#include "pch.h"
#include "Chip.h"

Chip::Chip(std::string goID, std::string filename, float x, float y, int rows, int cols, int value) : value(1)
{
	id = goID;

	left = new Button(id + "-left", "images/ARROWS.png", x, y + 10, 1, 2);
	chip = new Button(id + "-chip", filename, x + left->getWidth() + 3, y, rows, cols);
	right = new Button(id + "-right", "images/ARROWS.png", chip->getPosition().x + chip->getWidth() + 3, y + 10, 1, 2);

	addEventListener(Button::PRESSED, this, &Chip::onButtonDown);
	addEventListener(Button::RELEASED, this, &Chip::onButtonUp);

	setFrame(value);

	std::stringstream arrowName;
	arrowName << "left" << "-" << value;
	left->addFrame(arrowName.str(), 0, 27, 40, 1, 2);

	arrowName.str("");
	arrowName << "right" << "-" << value;
	right->addFrame(arrowName.str(), 1, 27, 40, 1, 2);
}

Chip::~Chip()
{
	delete chip;
	delete left;
	delete right;
}

void Chip::update(float delta)
{
	chip->update(delta);
	left->update(delta);
	right->update(delta);
}

void Chip::render()
{
	chip->render();
	left->render();
	right->render();
}

int Chip::getValue() const
{
	return value;
}

void Chip::onButtonDown(const UserEvent& e)
{

}

void Chip::onButtonUp(const UserEvent& e)
{

}

void Chip::setFrame(int v)
{
	switch (v)
	{
	case 1:
		chip->addFrame("1", 0, 65, 67, 2, 5);
		value = v;
		break;
	case 5:
		chip->addFrame("5", 1, 65, 67, 2, 5);
		value = v;
		break;
	case 10:
		chip->addFrame("10", 2, 65, 67, 2, 5);
		value = v;
		break;
	case 25:
		chip->addFrame("25", 3, 65, 67, 2, 5);
		value = v;
		break;
	case 50:
		chip->addFrame("50", 4, 65, 67, 2, 5);
		value = v;
		break;
	case 100:
		chip->addFrame("100", 5, 65, 67, 2, 5);
		value = v;
		break;
	case 500:
		chip->addFrame("500", 6, 65, 67, 2, 5);
		value = v;
		break;
	case 1000:
		chip->addFrame("1000", 7, 65, 67, 2, 5);
		value = v;
		break;
	case 5000:
		chip->addFrame("5000", 8, 65, 67, 2, 5);
		value = v;
		break;
	case 10000:
		chip->addFrame("10000", 9, 65, 67, 2, 5);
		value = v;
		break;
	}
}