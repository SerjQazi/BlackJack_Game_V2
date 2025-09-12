#pragma once

#include "GameObject.h"

class ResourceManager;

class SFX : public GameObject
{
public:
	SFX(std::string goID, std::string f);
	SFX(const SFX& other);
	~SFX();

	SFX* clone();

	void update(float);
	void render();

	void play(bool loop = false);
	void stop();
	void pause();
	void resume();

	bool isPlaying();
	bool isPaused();

	std::string filename;
	int channel;

private:
	Mix_Chunk* sfx;
};