#pragma once

#include "GameObject.h"
#include "Text.h"
#include "Chip.h"
#include "Button.h"
#include "Wallet.h"

class Bank : public GameObject
{
public:
	Bank(std::string goID, std::string filename, float x, float y, int rows, int cols, Wallet* w);
	~Bank();

	void update(float delta);
	void render();

	void reset();

	void onButtonDown(const UserEvent& e);
	void onButtonUp(const UserEvent& e);

	int getTotal() const;
	void setTotal(int t);

	void setWallet(Wallet* w);
	void setActive(bool a);

private:
	int total;
	std::stringstream displayText;
	Text* display;
	Chip* one;
	Chip* five;
	Chip* ten;
	Chip* fifty;
	Chip* onehundred;
	Chip* fivehundred;
	Chip* onethousand;
	Chip* fivethousand;
	Chip* tenthousand;
	Wallet* wallet;
};