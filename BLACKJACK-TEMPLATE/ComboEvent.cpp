#include "pch.h"

#include "ComboEvent.h"

ComboEvent::ComboEvent(const std::string& type, const SDL_Event& sdlEvent, std::vector<Key::Code> sequence) : UserEvent(type, sdlEvent), sequence(sequence)
{ }

std::vector<Key::Code> ComboEvent::getComboSequence() const
{
	return sequence;
}

const std::string ComboEvent::COMBO = "combo";