#pragma once

#include "Gameloop.h"
#include "Controller.h"
#include "Event.h"
#include "Key.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "ControllerEvent.h"
#include "UserEvent.h"
#include "ComboEvent.h"
#include "EventDispatcher.h"

class TimerManager;
class EventRegistry;

class InputManager
{
public:
	InputManager();
	~InputManager();

	static InputManager* getInstance();
	static void removeInstance();

	void handleEvents();
	bool checkCombo();

	void enableKeyboard();
	void enableMouse();
	
	void disableKeyboard();
	void disbaleMouse();

	static void pushUserEvent(std::string type, void* data1 = nullptr, void* data2 = nullptr);

private:
	bool keyboardEnabled;
	bool mouseEnabled;
	std::deque<Key::Code> keyHistory;
	std::unordered_map<SDL_JoystickID, Controller*> controllers;

	static InputManager* instance;
};