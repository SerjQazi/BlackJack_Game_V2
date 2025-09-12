#pragma once

#include "Font.h"

class Renderer;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* getInstance();
	static void removeInstance();

	static SDL_Surface* addSurface(std::string filename);
	static SDL_Texture* addTexture(std::string filename);
	static SDL_Texture* addTextTexture(std::string id, std::string text, const Font& font);
	static TTF_Font* addFont(std::string filename, int size);
	static Mix_Music* addMusic(std::string filename);
	static Mix_Chunk* addSFX(std::string filename);

	static void removeSurface(std::string filename);
	static void removeTexture(std::string filename);
	static void removeFont(std::string filename);
	static void removeMusic(std::string filename);
	static void removeSFX(std::string filename);

	static SDL_Surface* findSurface(std::string filename);
	static SDL_Texture* findTexture(std::string filename);
	static TTF_Font* findFont(std::string filename);
	static Mix_Music* findMusic(std::string filename);
	static Mix_Chunk* findSFX(std::string filename);

	static SDL_Texture* updateTextTexture(std::string id, std::string text, const Font& font);

	static std::unordered_map<std::string, SDL_Surface*> surfaceMap;
	static std::unordered_map<std::string, SDL_Texture*> textureMap;
	static std::unordered_map<std::string, TTF_Font*> fontMap;
	static std::unordered_map<std::string, Mix_Music*> musicMap;
	static std::unordered_map<std::string, Mix_Chunk*> sfxMap;

private:
	static ResourceManager* instance;
};