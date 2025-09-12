#pragma once

#include "GameObject.h"
#include "OpenGLVertex.h"
#include "OpenGLQuad.h"
#include "OpenGLBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GameConfiguration.h"

class OpenGLShader;
class ResourceManager;

class OpenGLImage : public GameObject
{
public:
	OpenGLImage(std::string goID, std::string filename, float x, float y, float width, float height, std::string vertexFilename, std::string fragFilename);
	~OpenGLImage();

	void update(float delta);
	void render();

	glm::vec2 position;
	float width;
	float height;

	GLuint textureID;

private:
	std::string filename;
	float frameWidth;
	float frameHeight;
	SDL_Surface* surface;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	
	OpenGLShader* shader;
	VertexArray* VAO;
	OpenGLBuffer* VBO;
	IndexBuffer* EBO;

	OpenGLQuad* quad;
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };
};