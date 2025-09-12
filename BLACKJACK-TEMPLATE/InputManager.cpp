#include "pch.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "EventRegistry.h"

InputManager::InputManager() : keyboardEnabled(true), mouseEnabled(true)
{ 
    LOG_INFO("Initializing input manager...");
    EventRegistry::getInstance()->registerEvent(ComboEvent::COMBO);
}

InputManager::~InputManager()
{ }

InputManager* InputManager::getInstance()
{
	if (instance == nullptr)
		instance = new InputManager();
	return instance;
}

void InputManager::removeInstance()
{
	if (instance)
		delete instance;
}

void InputManager::handleEvents()
{
    SDL_Event e;
    std::string eventType;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            Gameloop::running = false;
            break;
        case SDL_USEREVENT:
            eventType = EventRegistry::getInstance()->findEvent(e.user.code);
            LOG_INFO("User event: ", eventType);
            EventDispatcher::getInstance()->dispatchEvent(UserEvent(eventType, e));
            break;
        case SDL_KEYDOWN:
            if (keyboardEnabled)
            {
                LOG_INFO("Key pressed: ", SDL_GetKeyName(e.key.keysym.sym));
                keyHistory.push_back(Key(e.key.keysym.scancode).code);
                if (!checkCombo())
                    EventDispatcher::getInstance()->dispatchEvent(KeyboardEvent(KeyboardEvent::KEYDOWN, e));
            }
            break;
        case SDL_KEYUP:
            if (keyboardEnabled)
            {
                LOG_INFO("Key released: ", SDL_GetKeyName(e.key.keysym.sym));
                EventDispatcher::getInstance()->dispatchEvent(KeyboardEvent(KeyboardEvent::KEYUP, e));
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (mouseEnabled)
            {
                LOG_INFO("Mouse pressed at: (", e.button.x, ", ", e.button.y, ")");
                EventDispatcher::getInstance()->dispatchEvent(MouseEvent(MouseEvent::MOUSEDOWN, e));
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (mouseEnabled)
            {
                LOG_INFO("Mouse released at: (", e.button.x, ", ", e.button.y, ")");
                EventDispatcher::getInstance()->dispatchEvent(MouseEvent(MouseEvent::MOUSEUP, e));
            }
            break;
        case SDL_MOUSEMOTION:
            if (mouseEnabled)
            {
                LOG_INFO("Mouse position at: (", e.motion.x, ", ", e.motion.y, ")");
                EventDispatcher::getInstance()->dispatchEvent(MouseEvent(MouseEvent::MOUSEMOVE, e));
            }
            break;
        case SDL_CONTROLLERDEVICEADDED:
            controllers[e.cdevice.which] = new Controller(e.cdevice.which);
            controllers[e.cdevice.which]->enableSensors();
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            delete controllers[e.cdevice.which];
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            LOG_INFO("Controller Button Pressed: ", SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e.cbutton.button));
            EventDispatcher::getInstance()->dispatchEvent(ControllerEvent(ControllerEvent::CONTROLLERDOWN, e));
            break;
        case SDL_CONTROLLERBUTTONUP:
            LOG_INFO("Controller Button Released: ", SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e.cbutton.button));
            EventDispatcher::getInstance()->dispatchEvent(ControllerEvent(ControllerEvent::CONTROLLERUP, e));
            break;
        case SDL_CONTROLLERAXISMOTION:
            ControllerEvent event(ControllerEvent::CONTROLLERAXIS, e);
            controllers[e.cdevice.which]->updateAxisMotion(event);
            EventDispatcher::getInstance()->dispatchEvent(event);
            break;
        }
    }
}

bool InputManager::checkCombo()
{
    for (const auto& combo : EventRegistry::getInstance()->getCombos())
    {
        if (keyHistory.size() >= combo.size())
        {
            bool match = true;
            auto itHistory = keyHistory.rbegin();
            for (auto itCombo = combo.rbegin(); itCombo != combo.rend(); ++itCombo, ++itHistory)
            {
                if (*itCombo != *itHistory)
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                InputManager::pushUserEvent(ComboEvent::COMBO);
                keyHistory.clear();
                return true;
            }
        }
    }

    return false;
}

void InputManager::pushUserEvent(std::string type, void* data1, void* data2)
{
    Uint32 userType = SDL_RegisterEvents(1);
    if (userType != ((uint32_t)-1))
    {
        SDL_Event e;

        e.type = SDL_USEREVENT;
        e.user.type = SDL_USEREVENT;
        e.user.code = EventRegistry::getInstance()->generateCode(type);
        e.user.timestamp = TimerManager::getInstance()->findTimer("main")->getTicks();
        e.user.data1 = (void*)data1;
        e.user.data2 = (void*)data2;

        SDL_PushEvent(&e);
    }
    else
        LOG_ERROR("Cannot generate user event...");
}

void InputManager::enableKeyboard()
{
    keyboardEnabled = true;
}

void InputManager::enableMouse()
{
    mouseEnabled = true;
}

void InputManager::disableKeyboard()
{
    keyboardEnabled = false;
}

void InputManager::disbaleMouse()
{
    mouseEnabled = false;
}

InputManager* InputManager::instance = nullptr;