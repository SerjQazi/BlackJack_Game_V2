#pragma once
#include "Scene.h"
#include "Deck.h"
#include "Hand.h"
#include "Wallet.h"
#include "Bank.h"
#include "Image.h"
#include "Button.h"
#include "Text.h"

class LevelScene : public Scene
{
public:
    LevelScene(std::string id, Camera* c, World* w);
    ~LevelScene() override;

    void onEnter() override;
    void onExit() override;
    void update(float delta) override;
    void render() override;

private:
    // Game objects
    Deck* deck = nullptr;
    Image* bg;
    Image* chipbg;
    Image* table;
    Text* dealerLabel;
    Text* playerLabel;
    Wallet* wallet;
    Bank* bank;
    Button* playBtn;
    Button* betBtn;
    Button* hitBtn;
    Button* standBtn;
    Button* ddownBtn;
    Button* splitBtn;
    Button* quitBtn;

    // Game state
    enum class GameState { WaitingBet, PlayerTurn, DealerTurn, RoundOver };
    GameState state;

    std::vector<Hand> playerHands;
    Hand dealerHand;
    int currentHand = 0;
    int betTotal = 0;

    // Card layout offsets
    float playerOffsetX = 150.0f;
    float dealerOffsetX = 150.0f;

    // Event handlers
    void onKeyDown(const KeyboardEvent& e);
    void onButtonPressed(const UserEvent& e);

    // Button management
    void displayButtons(bool p, bool b, bool h, bool s, bool d, bool sp);

    // Game flow
    void startGame();
    void startRound();
    void play();
    void bet();
    void hit();
    void stand();
    void doubleDown();
    void split();
    void drawCard(Hand& hand, float yPos);
    void dealDealer();
};
