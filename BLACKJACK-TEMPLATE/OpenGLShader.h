#pragma once

#include "OpenGLImage.h"
#include "OpenGLVertex.h"

typedef enum shaderType
{
	VERTEX = 0,
	FRAGMENT,
	PROGRAM
} ShaderType;

class OpenGLImage;

class OpenGLShader
{
public:
	OpenGLShader(std::string = "", std::string = "");
	virtual ~OpenGLShader();

	void createShader(GLuint, GLuint);
	std::string loadShader(const std::string&);
	GLuint compileShader(const std::string&, ShaderType);
	void applyShader();
	void removeShader();

	void setBool(const std::string&, bool) const;
	void setInt(const std::string&, int) const;
	void setFloat(const std::string&, float) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	unsigned int shaderID;

	std::string vertexFilename;
	std::string fragmentFilename;

protected:
	void checkCompileErrors(unsigned int, ShaderType);

	std::string vertexCode;
	std::string fragmentCode;
};