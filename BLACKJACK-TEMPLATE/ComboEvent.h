#pragma once

#include "UserEvent.h"
#include "Key.h"

class ComboEvent : public UserEvent
{
public:
	ComboEvent(const std::string& type, const SDL_Event& sdlEvent, std::vector<Key::Code> sequence);

	std::vector<Key::Code> getComboSequence() const;
	
	static const std::string COMBO;

private:
	std::vector<Key::Code> sequence;
};