#pragma once

#include "GameObject.h"
#include "Text.h"

class Wallet : public GameObject
{
public:
	Wallet(std::string goID, float x, float y, int funds);
	~Wallet();

	void update(float delta);
	void render();

	void setVisible(bool v);

	int getTotal() const;
	void setTotal(int t);

private:
	int total;
	std::stringstream displayText;
	Text* display;
};