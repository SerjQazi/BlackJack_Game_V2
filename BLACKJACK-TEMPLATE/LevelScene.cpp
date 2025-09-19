#include "pch.h"
#include "LevelScene.h"
#include "Game.h"

LevelScene::LevelScene(std::string id, Camera* c, World* w) : Scene(id, c, w)
{
    betTotal = 0;
    deck = new Deck();

    bg = new Image("bg", "images/bg.png", 0.0f, 0.0f);
    chipbg = new Image("chipbg", "images/chipbg.png", 1025.0f, 0.0f);
    table = new Image("table", "images/table.png", 0.0f, 0.0f);

    dealerLabel = new Text("dealerLabel", "fonts/ds-digit.ttf", "DEALER", 5.0f, 10.0f, 70, { 255,255,0,255 });
    playerLabel = new Text("playerLabel", "fonts/ds-digit.ttf", "PLAYER", 5.0f, 250.0f, 70, { 255,255,0,255 });
    dealerLabel->setVisible(false);
    playerLabel->setVisible(false);

    wallet = new Wallet("wallet", 425.0f, 10.0f, 1000);
    bank = new Bank("chip", "images/CHIPS.png", 1050.0f, 20.0f, 2, 5, wallet);
    bank->setWallet(wallet);
    bank->setActive(false);
    wallet->setVisible(false);

    playBtn = new Button("play", "images/buttons.png", 50.0f, 680.0f, 1, 7);
    betBtn = new Button("bet", "images/buttons.png", 50.0f, 680.0f, 1, 7);
    hitBtn = new Button("hit", "images/buttons.png", 200.0f, 680.0f, 1, 7);
    standBtn = new Button("stand", "images/buttons.png", 350.0f, 680.0f, 1, 7);
    ddownBtn = new Button("ddown", "images/buttons.png", 500.0f, 680.0f, 1, 7);
    splitBtn = new Button("split", "images/buttons.png", 650.0f, 680.0f, 1, 7);
    quitBtn = new Button("quit", "images/buttons.png", 800.0f, 680.0f, 1, 7);

    playBtn->addFrame("play", 0, 134, 48, 1, 7);
    betBtn->addFrame("bet", 4, 134, 48, 1, 7);
    hitBtn->addFrame("hit", 2, 134, 48, 1, 7);
    standBtn->addFrame("stand", 3, 134, 48, 1, 7);
    ddownBtn->addFrame("ddown", 5, 134, 48, 1, 7);
    splitBtn->addFrame("split", 6, 134, 48, 1, 7);
    quitBtn->addFrame("quit", 1, 134, 48, 1, 7);
}

LevelScene::~LevelScene()
{
    delete deck;
}

void LevelScene::onEnter()
{
    addGameObject(bg, 0);
    addGameObject(chipbg, 0);
    addGameObject(table, 1);
    addGameObject(playBtn, 2);
    addGameObject(betBtn, 2);
    addGameObject(hitBtn, 2);
    addGameObject(standBtn, 2);
    addGameObject(ddownBtn, 2);
    addGameObject(splitBtn, 2);
    addGameObject(quitBtn, 2);
    addGameObject(dealerLabel, 2);
    addGameObject(playerLabel, 2);
    addGameObject(bank, 2);
    addGameObject(wallet, 2);

    addEventListener(KeyboardEvent::KEYDOWN, this, &LevelScene::onKeyDown);
    addEventListener(Button::PRESSED, this, &LevelScene::onButtonPressed);

    displayButtons(true, false, true, true, true, true);
}

void LevelScene::onExit()
{
    removeEventListener(KeyboardEvent::KEYDOWN, this, &LevelScene::onKeyDown);
    removeEventListener(Button::PRESSED, this, &LevelScene::onButtonPressed);
}

void LevelScene::update(float delta)
{
    Scene::update(delta);
}

void LevelScene::render()
{
    Scene::render();
}

void LevelScene::onKeyDown(const KeyboardEvent& e)
{
    if (e.key.code == Key::Code::Q)
    {
        Game::stop();
    }
}

void LevelScene::onButtonPressed(const UserEvent& e)
{
    std::string* buttonType = static_cast<std::string*>(e.getData1());

    if (*buttonType == "play" && playBtn->isVisible()) play();
    else if (*buttonType == "bet" && betBtn->isVisible()) bet();
    else if (*buttonType == "hit" && hitBtn->isVisible()) hit();
    else if (*buttonType == "stand" && standBtn->isVisible()) stand();
    else if (*buttonType == "ddown" && ddownBtn->isVisible()) doubleDown();
    else if (*buttonType == "split" && splitBtn->isVisible()) split();
    else if (*buttonType == "quit" && quitBtn->isVisible()) Game::stop();
}

void LevelScene::displayButtons(bool p, bool b, bool h, bool s, bool d, bool sp)
{
    playBtn->setVisible(p);
    betBtn->setVisible(b);
    hitBtn->setVisible(h);
    standBtn->setVisible(s);
    ddownBtn->setVisible(d);
    splitBtn->setVisible(sp);
}

void LevelScene::startGame()
{
    betTotal = 0;
    currentHand = 0;

    // Clear dealer hand
    for (auto card : dealerHand.getCards())
    {
        card->setVisible(false);
        removeGameObject(card);
    }
    dealerHand.clear();

    // Clear player hands
    for (auto& hand : playerHands)
    {
        for (auto card : hand.getCards())
        {
            card->setVisible(false);
            removeGameObject(card);
        }
        hand.clear();
    }
    playerHands.clear();

    dealerLabel->setText("DEALER");
    playerLabel->setText("PLAYER");
    dealerLabel->setVisible(true);
    playerLabel->setVisible(true);

    wallet->setVisible(true);
    bank->reset();
    bank->setActive(true);

    displayButtons(false, true, false, false, false, false);

    deck->shuffle();
}

void LevelScene::startRound()
{
    Hand playerHand;

    // Player cards
    Card* card = deck->dealCard();
    drawCard(playerHand, 320.0f);

    card = deck->dealCard();
    drawCard(dealerHand, 80.0f);

    card = deck->dealCard();
    drawCard(playerHand, 320.0f);

    card = deck->dealCard();
    drawCard(dealerHand, 80.0f);

    playerHands.push_back(playerHand);
}

void LevelScene::play() { startGame(); }

void LevelScene::bet()
{
    int credits = wallet->getTotal();

    bank->setActive(false);
    betTotal = bank->getTotal();

    startRound();

    // Show frames for cards
    for (auto card : playerHands[currentHand].getCards())
        card->setFrame(card->getObjectID());
    dealerHand.getCards()[0]->setFrame(dealerHand.getCards()[0]->getObjectID());

    displayButtons(false, false, true, true, true, true);
}

void LevelScene::hit()
{
    drawCard(playerHands[currentHand], 320.0f);

    if (playerHands[currentHand].getValue() > 21)
    {
        LOG_INFO("Player busted!");
        stand();
    }
}

void LevelScene::stand()
{
    if (currentHand + 1 < playerHands.size())
    {
        currentHand++;
    }
    else
    {
        dealDealer();
    }
}

void LevelScene::doubleDown()
{
    int currentBet = betTotal;

    if (wallet->getTotal() >= currentBet)
    {
        wallet->setTotal(wallet->getTotal() - currentBet);
        betTotal += currentBet;
    }

    drawCard(playerHands[currentHand], 320.0f);

    if (playerHands[currentHand].getValue() > 21)
    {
        LOG_INFO("Player busted on double down!");
    }

    stand();
}

void LevelScene::split()
{
    if (!playerHands[currentHand].canSplit()) return;

    Card* first = playerHands[currentHand].getCards()[0];
    Card* second = playerHands[currentHand].getCards()[1];

    if (wallet->getTotal() >= betTotal) wallet->setTotal(wallet->getTotal() - betTotal);

    // Keep first card in current hand
    playerHands[currentHand].clear();
    playerHands[currentHand].addCard(first);

    // New hand with second card
    Hand newHand;
    newHand.addCard(second);

    // Deal one new card to each hand
    drawCard(playerHands[currentHand], 320.0f);
    drawCard(newHand, 320.0f);

    playerHands.push_back(newHand);

    LOG_INFO("Player split hand into two!");
}

void LevelScene::drawCard(Hand& hand, float yPos)
{
    Card* card = deck->dealCard();
    card->setPosition(10 + (playerOffsetX * hand.getCards().size()), yPos);
    card->setFrame(card->getObjectID());
    hand.addCard(card);
    addGameObject(card, 3);
}

void LevelScene::dealDealer()
{
    state = GameState::DealerTurn;

    while (dealerHand.getValue() < 17)
    {
        drawCard(dealerHand, 80.0f);
    }

    // Compare dealer vs each player hand
    for (int i = 0; i < playerHands.size(); i++)
    {
        int playerValue = playerHands[i].getValue();
        int dealerValue = dealerHand.getValue();

        if (playerValue > 21)
        {
            LOG_INFO("Hand " + std::to_string(i + 1) + " busted! Dealer wins.");
        }
        else if (dealerValue > 21)
        {
            LOG_INFO("Dealer busted! Hand " + std::to_string(i + 1) + " wins!");
            wallet->setTotal(wallet->getTotal() + betTotal * 2);
        }
        else if (playerValue > dealerValue)
        {
            LOG_INFO("Hand " + std::to_string(i + 1) + " wins!");
            wallet->setTotal(wallet->getTotal() + betTotal * 2);
        }
        else if (playerValue < dealerValue)
        {
            LOG_INFO("Hand " + std::to_string(i + 1) + " loses!");
        }
        else
        {
            LOG_INFO("Hand " + std::to_string(i + 1) + " pushes (tie).");
            wallet->setTotal(wallet->getTotal() + betTotal);
        }
    }

    state = GameState::RoundOver;
    displayButtons(true, false, false, false, false, false);
}
