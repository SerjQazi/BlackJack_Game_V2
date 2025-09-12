#include "pch.h"
#include "Hand.h"

void Hand::addCard(Card* card) 
{
    cards.push_back(card);
}

std::vector<Card*> Hand::getCards() const 
{
    return cards;
}

int Hand::getValue() const 
{
    int total = 0;
    int numAces = 0;

    for (auto card : cards) 
    {
        int cardValue = card->getValue();
        if (card->rank == Ace) 
        {
            numAces++;
        }
        total += cardValue;
    }

    while (total > 21 && numAces > 0) 
    {
        total -= 10;
        numAces--;
    }

    return total;
}

void Hand::clear() 
{
    cards.clear();
}

bool Hand::canSplit() const 
{
    return cards.size() == 2 && cards[0]->rank == cards[1]->rank;
}