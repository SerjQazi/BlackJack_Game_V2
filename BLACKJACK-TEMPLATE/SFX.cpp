#include "pch.h"
#include "SFX.h"
#include "ResourceManager.h"

SFX::SFX(std::string goID, std::string f) : filename(f), channel(-1)
{
	id = goID;

	LOG_INFO("Creating SFX ", id, "...");

	sfx = ResourceManager::getInstance()->addSFX(filename);
}

SFX::SFX(const SFX& other) : filename(other.filename), channel(other.channel)
{
	id = other.id + "-clone";

	sfx = ResourceManager::getInstance()->addSFX(filename);
}

SFX::~SFX()
{
	LOG_INFO("Removing SFX ", id, "...");
}

SFX* SFX::clone()
{
	return new SFX(*this);
}

void SFX::update(float delta)
{

}

void SFX::render()
{

}

void SFX::play(bool loop)
{
	if (!isPlaying() && !isPaused())
	{
		int repeat = 0;
		if (loop)
			repeat = -1;

		channel = Mix_PlayChannel(-1, sfx, repeat);

		if (channel == -1)
		{
			LOG_ERROR("Cannot play sfx...");
		}

		LOG_INFO("Playing SFX ", id, "...");
	}
}

void SFX::stop()
{
	if (isPlaying() && !isPaused())
	{
		LOG_INFO("Stopping SFX...");
		Mix_HaltChannel(-1);
	}
}

void SFX::pause()
{
	if (isPlaying() && !isPaused())
	{
		LOG_INFO("Pausing SFX...");
		Mix_Pause(channel);
	}
}

void SFX::resume()
{
	if (isPlaying() && isPaused())
	{
		LOG_INFO("Resuming SFX...");
		Mix_Resume(channel);
	}
}

bool SFX::isPlaying()
{
	return Mix_Playing(channel) != 0;
}

bool SFX::isPaused()
{
	return Mix_Paused(channel) != 0;
}