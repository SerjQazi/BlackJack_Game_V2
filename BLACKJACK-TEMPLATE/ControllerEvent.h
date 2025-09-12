#pragma once

#include "Event.h"

class ControllerEvent : public Event
{
public:
	struct ControllerAxis
	{
		int xAxis;
		int yAxis;
		int xDirection;
		int yDirection;
		double angle;
	};

	ControllerEvent(const std::string& type, const SDL_Event& sdlEvent);

	SDL_JoystickID getJoystickID() const;
	Uint32 getTimestamp() const;
	Uint8 getButton() const;
	Uint8 getState() const;
	Uint8 getAxis() const;
	Sint16 getAxisValue() const;
	ControllerAxis& getControllerAxis(SDL_JoystickID jid);
	bool getControllerAxisState(int axis);

	void setControllerAxisState(int axis, bool state);

	static const std::string CONTROLLERDOWN;
	static const std::string CONTROLLERUP;
	static const std::string CONTROLLERAXIS;

private:
	Uint32 sdlType;
	SDL_JoystickID id;
	Uint32 timestamp;
	Uint8 button;
	Uint8 state;
	Uint8 axis;
	Sint16 axisValue;

	std::vector<ControllerAxis> controllerAxis;
	std::vector<bool> controllerAxisStates;
};