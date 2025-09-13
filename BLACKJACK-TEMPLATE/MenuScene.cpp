#include "pch.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "Renderer.h"

Image* bg;
Image* logo;
Button* playBtn;
Button* quitBtn;

MenuScene::MenuScene(std::string id, Camera* c, World* w) : Scene(id, c, w)
{
    int screenW, screenH;
    SDL_GetRendererOutputSize(Renderer::getSDLRenderer(), &screenW, &screenH);

    bg = new Image("bg", "images/bg.png", 0.0f, 0.0f, screenW, screenH);

    // Centered logo
    Image* tempLogo = new Image("logo", "images/logo.png", 0, 0);
    float logoX = (screenW - tempLogo->width) / 2.0f;
    float logoY = screenH * 0.2f;
    logo = new Image("logo", "images/logo.png", logoX, logoY);


    // Centered buttons with spacing
    float spacing = 100.0f; // space between buttons

    // First, get button dimensions
    float buttonW = 134.0f;  // frame width
    float buttonH = 48.0f;   // frame height

    // Total width of both buttons + spacing
    float totalW = (2 * buttonW) + spacing;

    // Start X so that both buttons are centered together
    float startX = (screenW - totalW) / 2.0f;
    float buttonY = screenH * 0.8f; // place near bottom (adjust as needed)

    playBtn = new Button("play", "images/buttons.png", startX, buttonY, 1, 7);
    quitBtn = new Button("quit", "images/buttons.png", startX + buttonW + spacing, buttonY, 1, 7);
    playBtn->addFrame("play", 0, 134, 48, 1, 7);
    quitBtn->addFrame("quit", 1, 134, 48, 1, 7);
}

void MenuScene::onEnter()
{
	addGameObject(bg, 0);
	addGameObject(logo, 1);
    addGameObject(playBtn, 2);
	addGameObject(quitBtn, 2);
   
    addEventListener(KeyboardEvent::KEYDOWN, this, &MenuScene::onKeyDown);
    addEventListener(Button::PRESSED, this, &MenuScene::onButtonPressed);
}

void MenuScene::onExit()
{
    removeAllGameObjects();
	
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

        SceneManager::getInstance()->removeScene();
        Game::getInstance()->createScene<LevelScene>("level1");
        Game::getInstance()->start();
    }

	else if (*buttonType == "quit")
	{
		Game::stop();
	}
}