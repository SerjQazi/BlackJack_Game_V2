#include "pch.h"
#include "OpenGLImage.h"
#include "OpenGLShader.h"
#include "ResourceManager.h"

OpenGLImage::OpenGLImage(std::string goID, std::string filename, float x, float y, float w, float h, std::string vertexFilename, std::string fragFilename) 
	: position{ x, y }, filename(filename), frameWidth(w), frameHeight(h)
{
	id = goID;
	
	LOG_INFO("Creating image ", id, "...");
	
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
	VBO->bufferData(quad->getVertices().size() * sizeof(OpenGLVertex), &quad->getVertices()[0], GL_STATIC_DRAW);
	VBO->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, position));
	VBO->vertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, color));
	VBO->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OpenGLVertex), (void*)offsetof(OpenGLVertex, texCoord));

	EBO = new IndexBuffer();
	EBO->bufferData(indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	VAO->unbind();
	VBO->unbind();
	EBO->unbind();
}

OpenGLImage::~OpenGLImage()
{
	LOG_INFO("Removing image ", id, "...");
	delete VAO;
	delete VBO;
	delete EBO;
	delete shader;
	delete quad;
	glDeleteTextures(1, &textureID);
	SDL_FreeSurface(surface);
}

void OpenGLImage::update(float delta)
{ }

void OpenGLImage::render()
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