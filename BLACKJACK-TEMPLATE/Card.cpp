#include "pch.h"
#include "Card.h"

Card::Card(Rank r, Suit s, std::string filename, float x, float y, int rows, int cols) : rank(r), suit(s)
{
    id = getName();

    sprite = new Sprite(id, filename, x, y, rows, cols);
}

Card::~Card()
{
    delete sprite;
}

void Card::update(float delta)
{
    sprite->update(delta);
}

void Card::render()
{
    sprite->render();
}

void Card::setPosition(float x, float y)
{
    sprite->position.x = x;
    sprite->position.y = y;
}

glm::vec2 Card::getPosition()
{
    return sprite->position;
}

void Card::addFrame(const std::string& name, const int startIndex, int width, int height, int rows, int cols)
{
    sprite->addAnimation(name, startIndex, 1, width, height, rows, cols);
    sprite->play(name, 1);
}

void Card::setFrame(const std::string& name)
{
    sprite->play(name, 1);
}

bool Card::isVisible()
{
    return sprite->visible;
}

void Card::setVisible(bool v)
{
    sprite->visible = v;
}

int Card::getValue() const {
    if (rank >= Two && rank <= Ten)
        return rank;
    else if (rank == Jack || rank == Queen || rank == King)
        return 10;
    else if (rank == Ace)
        return 11;
    return 0;
}

std::string Card::getName() const {
    std::string rank_str;
    switch (rank) {
    case Two: rank_str = "2"; break;
    case Three: rank_str = "3"; break;
    case Four: rank_str = "4"; break;
    case Five: rank_str = "5"; break;
    case Six: rank_str = "6"; break;
    case Seven: rank_str = "7"; break;
    case Eight: rank_str = "8"; break;
    case Nine: rank_str = "9"; break;
    case Ten: rank_str = "10"; break;
    case Jack: rank_str = "Jack"; break;
    case Queen: rank_str = "Queen"; break;
    case King: rank_str = "King"; break;
    case Ace: rank_str = "Ace"; break;
    default: rank_str = "?"; break;
    }

    std::string suit_str;
    switch (suit) {
    case Hearts: suit_str = "Hearts"; break;
    case Diamonds: suit_str = "Diamonds"; break;
    case Clubs: suit_str = "Clubs"; break;
    case Spades: suit_str = "Spades"; break;
    default: suit_str = "?"; break;
    }

    return rank_str + suit_str;
}