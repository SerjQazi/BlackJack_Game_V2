#include "pch.h"
#include "Deck.h"

Deck::Deck()
{
	cards.reserve(52);

	for (int s = Clubs; s <= Spades; ++s)
	{
		for (int r = Two; r <= Ace; ++r)
		{
			Card* card = new Card(static_cast<Rank>(r), static_cast<Suit>(s), "images/cards.png", 0.0f, 0.0f, 6, 9);
			card->addFrame(card->getName(), r + (s * 13), 117, 164, 6, 9);
			card->addFrame("back", 0, 117, 164, 6, 9);
			cards.push_back(card);
		}
	}

	currentCard = 0;
}

Deck::~Deck()
{
	LOG_INFO("Removing deck...");
	for (int i = currentCard; i < cards.size(); ++i)
		delete cards[i];

	cards.clear();
}

void Deck::shuffle() 
{
	std::random_device rd;
	std::mt19937 g(rd());
	
	for (auto card : cards)
	{
		card->setVisible(true);
		card->setFrame("back");
	}

	std::shuffle(cards.begin(), cards.end(), g);

	currentCard = 0;
}

Card* Deck::dealCard() 
{
	if (currentCard >= cards.size()) 
	{
		shuffle();
	}
	return cards[currentCard++];
}

void Deck::reset() 
{
	currentCard = 0;
}