#pragma once

#include "Game.h"
#include "Scene.h"
#include "GameConfiguration.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "UserEvent.h"
#include "Image.h"
#include "Button.h"

class MenuScene : public Scene
{
public:
	MenuScene(std::string id, Camera* c, World* w);
	~MenuScene() = default;

	void update(float delta);
	void render();

	void onEnter();
	void onExit();

	void onKeyDown(const KeyboardEvent& e);

	void onButtonPressed(const UserEvent& e);

private:

};