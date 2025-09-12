#pragma once

class OpenGLBuffer
{
public:
	OpenGLBuffer(GLenum type);
	virtual ~OpenGLBuffer();

	virtual void bufferData(GLsizeiptr size, void* data, GLenum usage);
	virtual void bind() const;
	virtual void unbind() const;
	virtual void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

protected:
	GLuint buffer;
	GLenum type;
};