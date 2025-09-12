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