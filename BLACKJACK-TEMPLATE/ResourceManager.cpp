#include "pch.h"
#include "ResourceManager.h"
#include "Renderer.h"

ResourceManager::ResourceManager()
{
	LOG_INFO("Initializing resource manager...");
	
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG_ERROR("Could not initialize SDL_mixer...");
	}

	Mix_AllocateChannels(8);
}

ResourceManager::~ResourceManager()
{
	for (auto item : textureMap)
	{
		if (item.second != nullptr)
		{
			LOG_INFO("Removing texture ", item.first, "...");
			SDL_DestroyTexture(item.second);
			item.second = nullptr;
		}
	}

	for (auto item : fontMap)
	{
		if (item.second != nullptr)
		{
			LOG_INFO("Removing font ", item.first, "...");
			TTF_CloseFont(item.second);
		}
	}

	for (auto item : musicMap)
	{
		if (item.second != nullptr)
		{
			LOG_INFO("Removing music ", item.first, "...");
			Mix_FreeMusic(item.second);
		}
	}

	for (auto item : sfxMap)
	{
		if (item.second != nullptr)
		{
			LOG_INFO("Removing SFX ", item.first, "...");
			Mix_FreeChunk(item.second);
		}
	}

	musicMap.clear();
	sfxMap.clear();
	textureMap.clear();
	fontMap.clear();

	Mix_CloseAudio();

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
}

ResourceManager* ResourceManager::getInstance()
{
	if (instance == nullptr)
		instance = new ResourceManager();
	return instance;
}

void ResourceManager::removeInstance()
{
	if (instance)
		delete instance;
}

SDL_Surface* ResourceManager::addSurface(std::string filename)
{
	SDL_Surface* surface = nullptr;
	GLenum format = 0;
	std::unordered_map<std::string, SDL_Surface*>::iterator it = surfaceMap.find(filename);

	if (it != surfaceMap.end())
	{
		LOG_WARNING("Sprite ", filename, " already loaded...");
		surface = (*it).second;
		return surface;
	}
	else
	{
		surface = IMG_Load(filename.c_str());

		LOG_INFO("Loading sprite ", filename, "...");

		if (surface == nullptr)
		{
			LOG_ERROR("Error: Unable to open surface...");
			return nullptr;
		}

		if (surface->pixels)
			surfaceMap[filename] = surface;
		else
			LOG_ERROR("Unable to create image...");
	}

	return surface;
}

SDL_Texture* ResourceManager::addTexture(std::string filename)
{
	SDL_Texture* texture;
	std::unordered_map<std::string, SDL_Texture*>::iterator it = textureMap.find(filename);

	if (it != textureMap.end())
	{
		LOG_WARNING("Sprite ", filename, " already loaded...");
		texture = (*it).second;
		return texture;
	}
	else
	{
		texture = IMG_LoadTexture(Renderer::getSDLRenderer(), filename.c_str());

		LOG_INFO("Loading sprite ", filename, "...");

		if (texture == nullptr)
		{
			LOG_ERROR("Error: Unable to open texture...");
			return nullptr;
		}
	}

	textureMap[filename] = texture;

	return texture;
}

SDL_Texture* ResourceManager::addTextTexture(std::string id, std::string text, const Font& font)
{
	SDL_Texture* texture;
	std::unordered_map<std::string, SDL_Texture*>::iterator it = textureMap.find(id);

	if (it != textureMap.end())
	{
		texture = (*it).second;
		return texture;
	}
	else
	{
		SDL_Surface* surface = TTF_RenderText_Blended(font.getSDLFont(), text.c_str(), font.getColor());
		texture = SDL_CreateTextureFromSurface(Renderer::getSDLRenderer(), surface);
		SDL_FreeSurface(surface);

		LOG_INFO("Loading text ", id, "...");

		if (texture == nullptr)
		{
			LOG_ERROR("Unable to open sprite...");
			return nullptr;
		}
	}

	textureMap[id] = texture;

	return texture;
}

TTF_Font* ResourceManager::addFont(std::string filename, int size)
{
	TTF_Font* font = nullptr;
	int fontHeight = 0;
	std::unordered_map<std::string, TTF_Font*>::iterator it = fontMap.find(filename);

	if (it != fontMap.end())
	{
		font = (*it).second;
		fontHeight = TTF_FontHeight(font);
	}

	if (fontHeight == size)
	{
		LOG_WARNING("Font ", filename, " already loaded...");

		return font;
	}
	else
	{
		font = TTF_OpenFont(filename.c_str(), size);

		LOG_INFO("Loading font ", filename, "...");

		if (font == nullptr)
		{
			LOG_ERROR("Unable to open font...");
			return nullptr;
		}
	}

	fontMap[filename] = font;

	return font;
}

Mix_Music* ResourceManager::addMusic(std::string filename)
{
	Mix_Music* music;
	std::unordered_map<std::string, Mix_Music*>::iterator it = musicMap.find(filename);

	if (it != musicMap.end())
	{
		LOG_WARNING("Music ", filename, "already loaded...");
		music = (*it).second;

		return music;
	}
	else
	{
		music = Mix_LoadMUS(filename.c_str());

		LOG_INFO("Loading music ", filename, "...");

		if (music == nullptr)
		{
			LOG_ERROR("Unable to open music...");
			return nullptr;
		}
	}

	musicMap[filename] = music;

	return music;
}

Mix_Chunk* ResourceManager::addSFX(std::string filename)
{
	Mix_Chunk* sfx;
	std::unordered_map<std::string, Mix_Chunk*>::iterator it = sfxMap.find(filename);

	if (it != sfxMap.end())
	{
		LOG_WARNING("SFX ", filename, " already loaded...");
		sfx = (*it).second;

		return sfx;
	}
	else
	{
		sfx = Mix_LoadWAV(filename.c_str());

		LOG_INFO("Loading SFX ", filename, "...");

		if (sfx == nullptr)
		{
			LOG_ERROR("Unable to open SFX...");
			return nullptr;
		}
	}

	sfxMap[filename] = sfx;

	return sfx;
}

void ResourceManager::removeSurface(std::string filename)
{
	SDL_Surface* surface = surfaceMap[filename];
	if (surface)
		SDL_FreeSurface(surface);
	surfaceMap.erase(filename);
}

void ResourceManager::removeTexture(std::string filename)
{
	SDL_Texture* texture = textureMap[filename];
	if (texture)
		SDL_DestroyTexture(texture);
	textureMap.erase(filename);
}

void ResourceManager::removeFont(std::string filename)
{
	TTF_Font* font = fontMap[filename];
	if (font)
		TTF_CloseFont(font);
	fontMap.erase(filename);
}

void ResourceManager::removeMusic(std::string filename)
{
	Mix_Music* music = musicMap[filename];
	if (music)
		Mix_FreeMusic(music);
	musicMap.erase(filename);
}

void ResourceManager::removeSFX(std::string filename)
{
	Mix_Chunk* sfx = sfxMap[filename];
	if (sfx)
		Mix_FreeChunk(sfx);
	sfxMap.erase(filename);
}

SDL_Surface* ResourceManager::findSurface(std::string filename)
{
	SDL_Surface* surface = surfaceMap[filename];
	if (surface == nullptr)
		return nullptr;
	return surface;
}

SDL_Texture* ResourceManager::findTexture(std::string filename)
{
	SDL_Texture* texture = textureMap[filename];
	if (texture == nullptr)
		return nullptr;
	return texture;
}

TTF_Font* ResourceManager::findFont(std::string filename)
{
	TTF_Font* font = fontMap[filename];
	if (font == nullptr)
		return nullptr;
	return font;
}

Mix_Music* ResourceManager::findMusic(std::string filename)
{
	Mix_Music* music = musicMap[filename];
	if (music == nullptr)
		return nullptr;
	return music;
}

Mix_Chunk* ResourceManager::findSFX(std::string filename)
{
	Mix_Chunk* sfx = sfxMap[filename];
	if (sfx == nullptr)
		return nullptr;
	return sfx;
}

SDL_Texture* ResourceManager::updateTextTexture(std::string id, std::string text, const Font& font)
{
	SDL_Texture* texture = nullptr;
	std::unordered_map<std::string, SDL_Texture*>::iterator it = textureMap.find(id);

	if (it != textureMap.end())
	{
		SDL_DestroyTexture((*it).second);

		SDL_Surface* surface = TTF_RenderText_Blended(font.getSDLFont(), text.c_str(), font.getColor());
		texture = SDL_CreateTextureFromSurface(Renderer::getSDLRenderer(), surface);
		SDL_FreeSurface(surface);

		if (texture == nullptr)
		{
			LOG_ERROR("Unable to open text...");
			return nullptr;
		}
	}

	textureMap[id] = texture;

	return texture;
}

std::unordered_map<std::string, SDL_Surface*> ResourceManager::surfaceMap;
std::unordered_map<std::string, TTF_Font*> ResourceManager::fontMap;
std::unordered_map<std::string, SDL_Texture*> ResourceManager::textureMap;
std::unordered_map<std::string, Mix_Music*> ResourceManager::musicMap;
std::unordered_map<std::string, Mix_Chunk*> ResourceManager::sfxMap;
ResourceManager* ResourceManager::instance;