#include "pch.h"
#include "Music.h"
#include "ResourceManager.h"

Music::Music(std::string goID, std::string f) : filename(f)
{
	id = goID;

	LOG_INFO("Creating music ", id, "...");

	music = ResourceManager::getInstance()->addMusic(filename);
}

Music::Music(const Music& other) : filename(other.filename)
{
	id = other.id + "-clone";

	music = ResourceManager::getInstance()->addMusic(filename);
}

Music::~Music()
{

}

Music* Music::clone()
{
	return new Music(*this);
}

void Music::update(float delta)
{

}

void Music::render()
{

}

void Music::play(bool loop)
{
	if (!isPlaying() && !isPaused())
	{
		int repeat = 0;
		if (loop)
			repeat = -1;

		Mix_PlayMusic(music, repeat);

		LOG_INFO("Playing music ", id, "...");
	}
}

void Music::stop()
{
	if (isPlaying() && !isPaused())
	{
		LOG_INFO("Stopping music ", id, "...");
		Mix_HaltMusic();
	}
}

void Music::pause()
{
	if (isPlaying() && !isPaused())
	{
		LOG_INFO("Pausing music ", id, "...");
		Mix_PauseMusic();
	}
}

void Music::resume()
{
	if (isPlaying() && isPaused())
	{
		LOG_INFO("Resuming music ", id, "...");
		Mix_ResumeMusic();
	}
}

bool Music::isPlaying()
{
	return Mix_PlayingMusic() != 0;
}

bool Music::isPaused()
{
	return Mix_PausedMusic() != 0;
}