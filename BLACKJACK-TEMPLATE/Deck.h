#pragma once

#include "Card.h"

class Deck 
{
public:
    Deck();
    ~Deck();

    void shuffle();
    Card* dealCard();
    void reset();

private:
    std::vector<Card*> cards;
    int currentCard;
};