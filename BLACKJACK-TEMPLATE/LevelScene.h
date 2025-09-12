#pragma once

#include "Game.h"
#include "Scene.h"
#include "GameConfiguration.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "UserEvent.h"
#include "Image.h"
#include "Deck.h"
#include "Hand.h"
#include "Button.h"
#include "Text.h"
#include "Wallet.h"
#include "Bank.h"

class LevelScene : public Scene
{
public:
	LevelScene(std::string id, Camera* c, World* w);
	~LevelScene() = default;

	void update(float delta);
	void render();

	void onEnter();
	void onExit();

	void onKeyDown(const KeyboardEvent& e);

	void onButtonPressed(const UserEvent& e);

	void displayButtons(bool p, bool b, bool h, bool s, bool d, bool sp);
	void startGame();
	void startRound();
	void play();
	void bet();
	void hit();
	void doubleDown();
	void stand();
	void split();

private:
	void dealDealer();
	void drawCard();

	Image* bg;
	Image* chipbg;
	Image* table;
	Text* dealerLabel;
	Text* playerLabel;

	Button* playBtn;
	Button* betBtn;
	Button* hitBtn;
	Button* standBtn;
	Button* ddownBtn;
	Button* splitBtn;
	Button* quitBtn;

	Deck* deck;
	Hand dealerHand;
	int currentHand;
	std::vector<Hand> playerHands;

	Bank* bank;
	Wallet* wallet;
	int betTotal;

	const float playerOffsetX = 150.0f;
};