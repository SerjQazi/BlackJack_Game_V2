#include "pch.h"
#include "Bank.h"

Bank::Bank(std::string goID, std::string filename, float x, float y, int rows, int cols, Wallet* w) : total(0), wallet(w)
{
	id = goID;
	displayText << "$ " << total;

	display = new Text("display", "fonts/ds-digit.ttf", displayText.str(), x, y, 48, { 255, 225, 0, 255 });
	one = new Chip("one", "images/CHIPS.png", x, y + 65, 2, 5, 1);
	five = new Chip("five", "images/CHIPS.png", x, y + 140, 2, 5, 5);
	ten = new Chip("ten", "images/CHIPS.png", x, y + 215, 2, 5, 10);
	fifty = new Chip("fifty", "images/CHIPS.png", x, y + 290, 2, 5, 50);
	onehundred = new Chip("onehundred", "images/CHIPS.png", x, y + 365, 2, 5, 100);
	fivehundred = new Chip("fivehundred", "images/CHIPS.png", x, y + 440, 2, 5, 500);
	onethousand = new Chip("onethousand", "images/CHIPS.png", x, y + 515, 2, 5, 1000);
	fivethousand = new Chip("fivethousand", "images/CHIPS.png", x, y + 590, 2, 5, 5000);
	tenthousand = new Chip("tenthousand", "images/CHIPS.png", x, y + 665, 2, 5, 10000);

	addEventListener(Button::PRESSED, this, &Bank::onButtonDown);
	addEventListener(Button::RELEASED, this, &Bank::onButtonUp);
}

Bank::~Bank()
{
	delete display;
	delete one;
	delete five;
	delete ten;
	delete fifty;
	delete onehundred;
	delete fivehundred;
	delete onethousand;
	delete fivethousand;
	delete tenthousand;
}

void Bank::update(float delta)
{
	display->update(delta);
	one->update(delta);
	five->update(delta);
	ten->update(delta);
	fifty->update(delta);
	onehundred->update(delta);
	fivehundred->update(delta);
	onethousand->update(delta);
	fivethousand->update(delta);
	tenthousand->update(delta);
}

void Bank::render()
{
	display->render();
	one->render();
	five->render();
	ten->render();
	fifty->render();
	onehundred->render();
	fivehundred->render();
	onethousand->render();
	fivethousand->render();
	tenthousand->render();
}

void Bank::reset()
{
	total = 0;
	displayText.str("");
	displayText << "$ " << total;
	display->setText(displayText.str());
}

void Bank::onButtonDown(const UserEvent& e)
{
	std::string* buttonType = static_cast<std::string*>(e.getData1());

	if (*buttonType == "one-left" && total - one->getValue() >= 0)
	{
		total -= one->getValue();
		wallet->setTotal(wallet->getTotal() + one->getValue());
	}
	else if (*buttonType == "one-right" && one->getValue() <= wallet->getTotal())
	{
		total += one->getValue();
		wallet->setTotal(wallet->getTotal() - one->getValue());
	}
	else if (*buttonType == "five-left" && total - five->getValue() >= 0)
	{
		total -= five->getValue();
		wallet->setTotal(wallet->getTotal() + five->getValue());
	}
	else if (*buttonType == "five-right" && five->getValue() <= wallet->getTotal())
	{
		total += five->getValue();
		wallet->setTotal(wallet->getTotal() - five->getValue());
	}
	else if (*buttonType == "ten-left" && total - ten->getValue() >= 0)
	{
		total -= ten->getValue();
		wallet->setTotal(wallet->getTotal() + ten->getValue());
	}
	else if (*buttonType == "ten-right" && ten->getValue() <= wallet->getTotal())
	{
		total += ten->getValue();
		wallet->setTotal(wallet->getTotal() - ten->getValue());
	}
	else if (*buttonType == "fifty-left" && total - fifty->getValue() >= 0)
	{
		total -= fifty->getValue();
		wallet->setTotal(wallet->getTotal() + fifty->getValue());
	}
	else if (*buttonType == "fifty-right" && fifty->getValue() <= wallet->getTotal())
	{
		total += fifty->getValue();
		wallet->setTotal(wallet->getTotal() - fifty->getValue());
	}
	else if (*buttonType == "onehundred-left" && total - onehundred->getValue() >= 0)
	{
		total -= onehundred->getValue();
		wallet->setTotal(wallet->getTotal() + onehundred->getValue());
	}
	else if (*buttonType == "onehundred-right" && onehundred->getValue() <= wallet->getTotal())
	{
		total += onehundred->getValue();
		wallet->setTotal(wallet->getTotal() - onehundred->getValue());
	}
	else if (*buttonType == "fivehundred-left" && total - fivehundred->getValue() >= 0)
	{
		total -= fivehundred->getValue();
		wallet->setTotal(wallet->getTotal() + fivehundred->getValue());
	}
	else if (*buttonType == "fivehundred-right" && fivehundred->getValue() <= wallet->getTotal())
	{
		total += fivehundred->getValue();
		wallet->setTotal(wallet->getTotal() - fivehundred->getValue());
	}
	else if (*buttonType == "onethousand-left" && total - onethousand->getValue() >= 0)
	{
		total -= onethousand->getValue();
		wallet->setTotal(wallet->getTotal() + onethousand->getValue());
	}
	else if (*buttonType == "onethousand-right" && onethousand->getValue() <= wallet->getTotal())
	{
		total += onethousand->getValue();
		wallet->setTotal(wallet->getTotal() - onethousand->getValue());
	}
	else if (*buttonType == "fivethousand-left" && total - fivethousand->getValue() >= 0)
	{
		total -= fivethousand->getValue();
		wallet->setTotal(wallet->getTotal() + fivethousand->getValue());
	}
	else if (*buttonType == "fivethousand-right" && fivethousand->getValue() <= wallet->getTotal())
	{
		total += fivethousand->getValue();
		wallet->setTotal(wallet->getTotal() - fivethousand->getValue());
	}
	else if (*buttonType == "tenthousand-left" && total - tenthousand->getValue() >= 0)
	{
		total -= tenthousand->getValue();
		wallet->setTotal(wallet->getTotal() + tenthousand->getValue());
	}
	else if (*buttonType == "tenthousand-right" && tenthousand->getValue() <= wallet->getTotal())
	{
		total += tenthousand->getValue();
		wallet->setTotal(wallet->getTotal() - tenthousand->getValue());
	}

	displayText.str("");
	displayText << "$ " << total;
	display->setText(displayText.str());
}

void Bank::onButtonUp(const UserEvent& e)
{

}

int Bank::getTotal() const
{
	return total;
}

void Bank::setTotal(int t)
{
	total = t;

	displayText.str("");
	displayText << "$ " << total;
	display->setText(displayText.str());
}

void Bank::setWallet(Wallet* w)
{
	wallet = w;
}

void Bank::setActive(bool a)
{
	if (a)
	{
		addEventListener(Button::PRESSED, this, &Bank::onButtonDown);
		addEventListener(Button::RELEASED, this, &Bank::onButtonUp);
	}
	else
	{
		removeEventListener(Button::PRESSED, this, &Bank::onButtonDown);
		removeEventListener(Button::RELEASED, this, &Bank::onButtonUp);
	}
}