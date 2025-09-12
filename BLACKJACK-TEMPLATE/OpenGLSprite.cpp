#include "pch.h"
#include "OpenGLSprite.h"
#include "OpenGLShader.h"
#include "AnimationManager.h"
#include "ResourceManager.h"
#include "ConfigurationManager.h"

OpenGLSprite::OpenGLSprite(std::string goID, std::string filename, float x, float y, float w, float h, std::string vertexFilename, std::string fragFilename, bool f)
	: position{ x, y }, filename(filename), frameWidth(w), frameHeight(h), currentAnimation(nullptr), animating(false), flip(f)
{
	id = goID;

	LOG_INFO("Creating sprite ", id, "...");

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = 0;
	SDL_Surface* surface = ResourceManager::addSurface(filename);

	width = static_cast<float>(surface->w);
	height = static_cast<float>(surface->h);

	if (surface->format->BytesPerPixel == 3)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
	}
	else if (surface->format->BytesPerPixel == 4)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
	}

	if (surface->pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, format, GL_UNSIGNED_BYTE, surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		LOG_ERROR("Unable to create image...");
	}

	quad = new OpenGLQuad(position.x, position.y, frameWidth, frameHeight, width, height);

	shader = new OpenGLShader(vertexFilename, fragFilename);
	VAO = new VertexArray();

	VBO = new OpenGLBuffer(GL_ARRAY_BUFFER);
	VBO->bufferData(quad->getVertices().size() * sizeof(OpenGLVertex), &quad->getVertices()[0], GL_DYNAMIC_DRAW);
	VBO->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, position));
	VBO->vertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, color));
	VBO->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, texCoord));

	EBO = new IndexBuffer();
	EBO->bufferData(indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	VAO->unbind();
	VBO->unbind();
	EBO->unbind();
}

OpenGLSprite::OpenGLSprite(std::string goID, std::string filename, float x, float y, std::string vertexFilename, std::string fragFilename, bool f)
	: position{ x, y }, animating(false), currentAnimation(nullptr), flip(f)
{
	SpriteConfiguration* config = new SpriteConfiguration();
	ConfigurationManager::getInstance()->loadConfiguration(filename, config);

	id = goID;

	LOG_INFO("Creating sprite ", id, " from file ", filename, "...");

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = 0;
	filename = config->filename;
	frameWidth = config->frameWidth;
	frameHeight = config->frameHeight;
	SDL_Surface* surface = ResourceManager::getInstance()->addSurface(filename);

	for (auto item : config->animations)
	{
		Animation sequence = config->animations[item.first];
		int numFrames = static_cast<int>(sequence.frames.size());
		float duration = 1.0f / numFrames;
		sequence.fps = 1 / duration;
		addAnimation(item.first, sequence);
	}

	width = static_cast<float>(surface->w);
	height = static_cast<float>(surface->h);

	if (surface->format->BytesPerPixel == 3)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
	}
	else if (surface->format->BytesPerPixel == 4)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
	}

	if (surface->pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, format, GL_UNSIGNED_BYTE, surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		LOG_ERROR("Unable to create image...");
	}

	quad = new OpenGLQuad(position.x, position.y, frameWidth, frameHeight, width, height);

	shader = new OpenGLShader(vertexFilename, fragFilename);
	VAO = new VertexArray();

	VBO = new OpenGLBuffer(GL_ARRAY_BUFFER);
	VBO->bufferData(quad->getVertices().size() * sizeof(OpenGLVertex), &quad->getVertices()[0], GL_DYNAMIC_DRAW);
	VBO->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, position));
	VBO->vertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, color));
	VBO->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, texCoord));

	EBO = new IndexBuffer();
	EBO->bufferData(indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	VAO->unbind();
	VBO->unbind();
	EBO->unbind();
}

OpenGLSprite::~OpenGLSprite()
{
	LOG_INFO("Removing image ", id, "...");
	delete VAO;
	delete VBO;
	delete EBO;
	delete shader;
	delete quad;
	glDeleteTextures(1, &textureID);
}

void OpenGLSprite::update(float delta)
{ 
	if (animating)
	{
		currentAnimation->elapsedTime += delta;
		float totalDuration = 0.0;
		for (const Frame& frame : currentAnimation->frames)
		{
			totalDuration += (1000.0f / currentAnimation->fps) / 1000.0f;
		}

		float progress = static_cast<float>(currentAnimation->elapsedTime) / totalDuration;
		int frameCount = static_cast<int>(currentAnimation->frames.size());
		currentAnimation->currentFrameIndex = static_cast<int>(progress * frameCount) % frameCount;
		quad->transform(position.x, position.y, width, height, currentAnimation->getCurrentFrame(), flip);
		VBO->bind();
		VBO->bufferData(quad->getVertices().size() * sizeof(OpenGLVertex), &quad->getVertices()[0], GL_DYNAMIC_DRAW);
		VBO->unbind();
	}
}

void OpenGLSprite::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	shader->applyShader();
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	shader->setInt("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	VAO->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->removeShader();
}

void OpenGLSprite::addAnimation(const std::string& name, const Animation& animation)
{
	AnimationManager::getInstance()->addAnimation(name, animation);
}

void OpenGLSprite::addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps, bool loop, bool reverse, bool flip)
{
	SDL_RendererFlip orientation = (flip) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	AnimationManager::getInstance()->addAnimation(name, startIndex, length, frameWidth, frameHeight, rows, cols, fps, loop, reverse, orientation);
}

void OpenGLSprite::removeAnimation(const std::string& name)
{
	AnimationManager::getInstance()->removeAnimation(name);
}

void OpenGLSprite::play(const std::string& name)
{
	LOG_INFO("Playing ", id, " animation ", name, "...");

	currentAnimation = AnimationManager::getInstance()->setCurrentAnimation(name);
	animating = true;
}

void OpenGLSprite::play(std::string name, float fps, bool l, bool r, bool f)
{
	LOG_INFO("Playing ", id, " animation ", name, "...");

	flip = f;

	currentAnimation = AnimationManager::getInstance()->setCurrentAnimation(name);
	currentAnimation->fps = fps;
	currentAnimation->loop = l;
	currentAnimation->reverse = r;
	currentAnimation->orientation = static_cast<SDL_RendererFlip>(flip);
	animating = true;
}

void OpenGLSprite::stop()
{
	LOG_INFO("Stopping ", id, " animation...");

	animating = false;
}

bool OpenGLSprite::getFlip() const
{
	return flip;
}

void OpenGLSprite::setFlip(bool f)
{
	flip = f;
}

void OpenGLSprite::setFPS(std::string goID, float fps)
{
	AnimationManager::getInstance()->setFPS(goID, fps);
}