#pragma once

#include "Configuration.h"
#include "Frame.h"
#include "Animation.h"

class SpriteConfiguration : public Configuration
{
public:
	SpriteConfiguration();

	std::string filename;
	std::string id;
	int rows;
	int cols;
	int frameWidth;
	int frameHeight;
	int spriteSheetWidth;
	int spriteSheetHeight;
	std::multimap<std::string, Frame> frames;
	std::map<std::string, Animation> animations;
};