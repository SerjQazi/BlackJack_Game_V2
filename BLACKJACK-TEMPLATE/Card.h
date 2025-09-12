#pragma once

#include "GameObject.h"
#include "Sprite.h"

enum Suit { Clubs, Diamonds, Hearts, Spades };
enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card : public GameObject {
public:
	Card(Rank r, Suit s, std::string filename, float x, float y, int rows, int cols);
	~Card();

	void update(float delta);
	void render();

	void setPosition(float x, float y);
	glm::vec2 getPosition();

	void addFrame(const std::string& name, const int startIndex, int width, int height, int rows, int cols);
	void setFrame(const std::string& name);

	bool isVisible();
	void setVisible(bool v);

    int getValue() const;
    std::string getName() const;

    Suit suit;
    Rank rank;

private:
	Sprite* sprite;
};