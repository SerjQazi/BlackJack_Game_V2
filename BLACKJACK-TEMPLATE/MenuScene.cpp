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

    // First, get button dimensions (assuming Button has width/height members after frame setup)
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
	/*delete playBtn;
	delete quitBtn;*/

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

    void* data = e.getData1();
    if (!data) return;
    std::string* buttonType = static_cast<std::string*>(data);
    if (!buttonType) return;

    //std::string* buttonType = static_cast<std::string*>(e.getData1());

 //   if (*buttonType == "play" && playBtn->isVisible())
 //   {
 //       LOG_INFO("PLAY Pressed");
 //       // remove current/menu scene
	//	Game* game = Game::getInstance("");
	//	game->removeScene();

	//}
  //  if (*buttonType == "play" && playBtn->isVisible())
  //  {
  //      LOG_INFO("PLAY Pressed");

  //      // Use the singleton Game instance created in main
  //      Game* game = Game::getInstance("");

  //      // 1) remove the menu scene (this scene)

		//game->removeScene("menu");
  //      
  //      //game->removeScene();

  //      // 2) create the level scene (registered with SceneManager)
  //      LevelScene* level = game->createScene<LevelScene>("level1");

  //      // 3) explicitly initialize the new scene so it becomes active immediately
  //      if (level) level->onEnter();

  //      
  //  }
    if (*buttonType == "play" && playBtn->isVisible())
    {
        LOG_INFO("PLAY Pressed");

        Game* game = Game::getInstance("");

        // 1) create the level scene first
        LevelScene* level = game->createScene<LevelScene>("level1");

        if (level)
        {
            // 2) switch to it (your engine might have setActiveScene or similar)
            game->createScene<LevelScene>("level1");

            // 3) now safely remove the menu scene if you want
            game->removeScene();
            Game::start();
        }
        else
        {
            LOG_ERROR("Failed to create LevelScene!");
        }
    }

	else if (*buttonType == "quit")
	{
		Game::stop();
	}

  
}