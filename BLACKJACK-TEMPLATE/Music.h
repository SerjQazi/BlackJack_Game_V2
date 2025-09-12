#pragma once

#include "GameObject.h"

class ResourceManager;

class Music : public GameObject
{
public:
	Music(std::string goID, std::string f);
	Music(const Music& other);
	~Music();

	Music* clone();

	void update(float);
	void render();

	void play(bool loop = false);
	void stop();
	void pause();
	void resume();

	bool isPlaying();
	bool isPaused();

	std::string filename;

private:
	Mix_Music* music;
};