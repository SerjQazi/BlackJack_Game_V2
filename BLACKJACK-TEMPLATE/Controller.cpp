#include "pch.h"

#include "Controller.h"

Controller::Controller(SDL_JoystickID jid) : id(jid), controller(nullptr), joystick(nullptr)
{
    LOG_INFO("Controller ", id, " added...");

	if (SDL_IsGameController(id) && !SDL_GameControllerGetAttached(controller))
	{
        SDL_GameControllerAddMapping("4c05c405000000000000504944564944, PS4 Controller,a:b1,b:b2,back:b8,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b4,leftstick:b10,lefttrigger:a3,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b11,righttrigger:a4,rightx:a2,righty:a5,start:b9,touchpad:b13,x:b0,y:b3,");
		
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            controller = SDL_GameControllerOpen(id);
            if (controller)
            {
                joystick = SDL_GameControllerGetJoystick(controller);
                LOG_INFO("Opened game controller ", SDL_GameControllerName(controller), " with joystick ID ", id, "...");

                if (SDL_JoystickEventState(SDL_ENABLE) < 0)
                    LOG_INFO("Joystick not initialized...");
            }
            else
                LOG_ERROR("Controller not connected...");
        }
	}
}

Controller::~Controller()
{
    LOG_INFO("Controller ", id, " removed...");
	SDL_GameControllerClose(controller);
}

void Controller::enableSensors()
{
    if (SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_GYRO, SDL_TRUE) < 0)
        LOG_ERROR("Could not enable gyro sensor...");

    if (SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_ACCEL, SDL_TRUE) < 0)
        LOG_ERROR("Could not enable accelerometer sensor...");
}

void Controller::updateAxisMotion(ControllerEvent& e)
{
    if (e.getAxisValue() < -JOYSTICK_DEADZONE || e.getAxisValue() > JOYSTICK_DEADZONE)
    {
        ControllerEvent::ControllerAxis& axis = e.getControllerAxis(e.getJoystickID());
        switch (e.getAxis())
        {
        case SDL_CONTROLLER_AXIS_LEFTX:
            e.setControllerAxisState(LEFTX, true);
            axis.xDirection = (e.getAxisValue() < -JOYSTICK_DEADZONE) ? -1 : 1;
            LOG_INFO("Controller ", e.getJoystickID(), " left X axis moved...");
            break;

        case SDL_CONTROLLER_AXIS_LEFTY:
            e.setControllerAxisState(LEFTY, true);
            axis.yDirection = (e.getAxisValue() < -JOYSTICK_DEADZONE) ? -1 : 1;
            LOG_INFO("Controller ", e.getJoystickID(), " left Y axis moved...");
            break;

        case SDL_CONTROLLER_AXIS_RIGHTX:
            e.setControllerAxisState(RIGHTX, true);
            axis.xDirection = (e.getAxisValue() < -JOYSTICK_DEADZONE) ? -1 : 1;
            LOG_INFO("Controller ", e.getJoystickID(), " right X axis moved...");
            break;

        case SDL_CONTROLLER_AXIS_RIGHTY:
            e.setControllerAxisState(RIGHTY, true);
            axis.yDirection = (e.getAxisValue() < -JOYSTICK_DEADZONE) ? -1 : 1;
            LOG_INFO("Controller ", e.getJoystickID(), " right Y axis moved...");
            break;

        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
            e.setControllerAxisState(TRIGGERLEFT, true);
            LOG_INFO("Controller ", e.getJoystickID(), " left trigger axis moved...");
            break;

        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
            e.setControllerAxisState(TRIGGERRIGHT, true);
            LOG_INFO("Controller ", e.getJoystickID(), " right trigger axis moved...");
            break;

        default:
            break;
        }

        axis.xAxis = SDL_JoystickGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTX);
        axis.yAxis = SDL_JoystickGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTY);
        axis.angle = atan2(static_cast<double>(axis.yDirection), static_cast<double>(axis.xDirection)) * (180.0 / M_PI);

        if (axis.xDirection == 0 && axis.yDirection == 0)
        {
            axis.angle = 0;
        }
    }
}

const int Controller::JOYSTICK_DEADZONE = 8000;