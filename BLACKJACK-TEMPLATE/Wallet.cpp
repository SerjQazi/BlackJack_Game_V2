#include "pch.h"
#include "Wallet.h"

Wallet::Wallet(std::string goID, float x, float y, int funds) : total(funds)
{
	id = goID;
	displayText << "$ " << total;
	display = new Text("walletDisplay", "fonts/ds-digit.ttf", displayText.str(), x, y, 70, { 255, 255, 0, 255 });
}

Wallet::~Wallet()
{
	delete display;
}

void Wallet::update(float delta)
{
	display->update(delta);
}

void Wallet::render()
{
	display->render();
}

void Wallet::setVisible(bool v)
{
	display->setVisible(v);
}

void Wallet::setTotal(int t)
{
	total = t;
	displayText.str("");
	displayText << "$ " << total;
	display->setText(displayText.str());
}

int Wallet::getTotal() const
{
	return total;
}