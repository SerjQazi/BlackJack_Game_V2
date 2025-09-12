#include "pch.h"
#include "ControllerEvent.h"

ControllerEvent::ControllerEvent(const std::string& type, const SDL_Event& sdlEvent) : Event(type, sdlEvent)
{
    sdlType = sdlEvent.type;
    id = sdlEvent.cdevice.which;

    int numJoysticks = SDL_NumJoysticks();
    for (int i = 0; i < numJoysticks; ++i)
    {
        if (SDL_IsGameController(i))
        {
            ControllerAxis temp;
            temp.xAxis = 0;
            temp.yAxis = 0;
            temp.xDirection = 0;
            temp.yDirection = 0;
            controllerAxis.push_back(temp);
        }
    }

    for (int i = 0; i < 6; ++i)
        controllerAxisStates.push_back(false);

    if (sdlEvent.type == SDL_CONTROLLERBUTTONDOWN || sdlEvent.type == SDL_CONTROLLERBUTTONUP)
    {
        timestamp = sdlEvent.cbutton.timestamp;
        button = sdlEvent.cbutton.button;
        state = sdlEvent.cbutton.state;
        axis = 0;
        axisValue = 0;
    }
    else if (sdlEvent.type == SDL_CONTROLLERAXISMOTION)
    {
        timestamp = sdlEvent.caxis.timestamp;
        button = 0;
        state = 0;
        axis = sdlEvent.caxis.axis;
        axisValue = sdlEvent.caxis.value;
    }
}

SDL_JoystickID ControllerEvent::getJoystickID() const
{
    return id;
}

Uint32 ControllerEvent::getTimestamp() const
{
    return timestamp;
}

Uint8 ControllerEvent::getButton() const
{
    return button;
}

Uint8 ControllerEvent::getState() const
{
    return state;
}

Uint8 ControllerEvent::getAxis() const
{
    return axis;
}

Sint16 ControllerEvent::getAxisValue() const
{
    return axisValue;
}

ControllerEvent::ControllerAxis& ControllerEvent::getControllerAxis(SDL_JoystickID jid)
{
    return controllerAxis[jid];
}

bool ControllerEvent::getControllerAxisState(int axis)
{
    return controllerAxisStates[axis];
}

void ControllerEvent::setControllerAxisState(int axis, bool state)
{
    controllerAxisStates[axis] = state;
}

const std::string ControllerEvent::CONTROLLERDOWN = "controllerdown";
const std::string ControllerEvent::CONTROLLERUP = "controllerup";
const std::string ControllerEvent::CONTROLLERAXIS = "controlleaxis";