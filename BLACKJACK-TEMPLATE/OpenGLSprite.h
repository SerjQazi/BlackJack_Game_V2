#pragma once

#include "GameObject.h"
#include "OpenGLVertex.h"
#include "OpenGLQuad.h"
#include "OpenGLBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Animation.h"
#include "GameConfiguration.h"
#include "SpriteConfiguration.h"

class OpenGLShader;
class ResourceManager;
class AnimationManager;
class ConfigurationManager;

class OpenGLSprite : public GameObject
{
public:
	OpenGLSprite(std::string goID, std::string filename, float x, float y, float width, float height, std::string vertexFilename, std::string fragFilename, bool f = false);
	OpenGLSprite(std::string goID, std::string filename, float x, float y, std::string vertexFilename, std::string fragFilename, bool f = false);
	virtual ~OpenGLSprite();

	virtual void update(float delta);
	virtual void render();

	void addAnimation(const std::string& name, const Animation& animation);
	void addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps = 0.0f, bool loop = true, bool reverse = false, bool flip = false);
	void removeAnimation(const std::string& name);
	
	void play(const std::string& name);
	void play(std::string name, float fps, bool l = false, bool r = false, bool f = false);
	void stop();

	void setFPS(std::string goID, float fps);

	bool getFlip() const;
	void setFlip(bool f);

	glm::vec2 position;
	float width;
	float height;
	float frameWidth;
	float frameHeight;
	
	GLuint textureID;

protected:
	std::string filename;

	bool flip;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	OpenGLShader* shader;
	VertexArray* VAO;
	OpenGLBuffer* VBO;
	IndexBuffer* EBO;

	OpenGLQuad* quad;
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };

	bool animating;
	Animation* currentAnimation;
};