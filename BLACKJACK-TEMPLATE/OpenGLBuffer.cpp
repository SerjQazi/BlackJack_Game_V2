#include "pch.h"
#include "OpenGLBuffer.h"

OpenGLBuffer::OpenGLBuffer(GLenum type) : buffer(0)
{
	this->type = type;
	glGenBuffers(1, &buffer);
}

OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteBuffers(1, &buffer);
	this->unbind();
}

void OpenGLBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage)
{
	this->bind();
	glBufferData(this->type, size, data, usage);
}

void OpenGLBuffer::bind() const
{
	glBindBuffer(this->type, buffer);
}

void OpenGLBuffer::unbind() const
{
	glBindBuffer(type, 0);
}

void OpenGLBuffer::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	this->bind();
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}