#include "pch.h"
#include "MenuScene.h"
#include "LevelScene.h"

Button* playBtn;
Button* quitBtn;

MenuScene::MenuScene(std::string id, Camera* c, World* w) : Scene(id, c, w)
{
    playBtn = new Button("play", "images/buttons.png", 50.0f, 680.0f, 1, 7);
    quitBtn = new Button("quit", "images/buttons.png", 800.0f, 680.0f, 1, 7);
    playBtn->addFrame("play", 0, 134, 48, 1, 7);
    quitBtn->addFrame("quit", 1, 134, 48, 1, 7);
}

void MenuScene::onEnter()
{
	addGameObject(playBtn, 2);
	addGameObject(quitBtn, 2);
   
    addEventListener(KeyboardEvent::KEYDOWN, this, &MenuScene::onKeyDown);
    addEventListener(Button::PRESSED, this, &MenuScene::onButtonPressed);
}

void MenuScene::onExit()
{
    removeAllGameObjects();
	delete playBtn;
	delete quitBtn;

    removeEventListener(KeyboardEvent::KEYDOWN, this, &MenuScene::onKeyDown);
    removeEventListener(Button::PRESSED, this, &MenuScene::onButtonPressed);
}

void MenuScene::update(float delta)
{
    Scene::update(delta);
}

void MenuScene::render()
{
    Scene::render();
}

void MenuScene::onKeyDown(const KeyboardEvent& e)
{
    if (e.key.code == Key::Code::Q)
    {
        Game::stop();
    }
}

void MenuScene::onButtonPressed(const UserEvent& e)
{
    std::string* buttonType = static_cast<std::string*>(e.getData1());

    if (*buttonType == "play" && playBtn->isVisible())
    {
        LOG_INFO("PLAY Pressed");
	}
	else if (*buttonType == "quit")
	{
		Game::stop();
	}

    
}