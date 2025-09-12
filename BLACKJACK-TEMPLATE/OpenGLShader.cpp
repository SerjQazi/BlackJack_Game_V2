#include "pch.h"
#include "OpenGLShader.h"
#include "OpenGLImage.h"

OpenGLShader::OpenGLShader(std::string vertexPath, std::string fragmentPath) : vertexFilename(vertexPath), fragmentFilename(fragmentPath)
{
	vertexCode = loadShader(vertexFilename);
	fragmentCode = loadShader(fragmentFilename);

	GLuint vertex = compileShader(vertexCode.c_str(), ShaderType::VERTEX);
	GLuint fragment = compileShader(fragmentCode.c_str(), ShaderType::FRAGMENT);

	createShader(vertex, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

OpenGLShader::~OpenGLShader()
{
	LOG_INFO("Removing shader...");

	glDeleteProgram(shaderID);
}

std::string OpenGLShader::loadShader(const std::string& filename)
{
	std::stringstream buffer;

	try
	{
		std::ifstream file(filename);

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		buffer << file.rdbuf();

		return buffer.str();
	}
	catch (std::ifstream::failure& e)
	{
		LOG_ERROR("Shader could not be opened...");
	}

	return buffer.str();
}

void OpenGLShader::createShader(GLuint vertex, GLuint fragment)
{
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	glValidateProgram(shaderID);
	checkCompileErrors(shaderID, ShaderType::PROGRAM);
}

GLuint OpenGLShader::compileShader(const std::string& shaderData, ShaderType shaderType)
{
	GLenum type;

	LOG_INFO("Compiling shader...");
	if (shaderType == ShaderType::VERTEX)
		type = GL_VERTEX_SHADER;
	if (shaderType == ShaderType::FRAGMENT)
		type = GL_FRAGMENT_SHADER;

	GLuint shader = glCreateShader(type);
	const char* source = shaderData.c_str();

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	checkCompileErrors(shader, shaderType);
	
	LOG_INFO("Shader compiled...");

	return shader;
}

void OpenGLShader::applyShader()
{
	glUseProgram(shaderID);
}

void OpenGLShader::removeShader()
{
	glUseProgram(0);
}

void OpenGLShader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void OpenGLShader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void OpenGLShader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat) const 
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void OpenGLShader::checkCompileErrors(unsigned int shader, ShaderType type)
{
	int success;
	char infoLog[1024];
	if (type != ShaderType::PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			LOG_ERROR("Shader could not be compiled...");
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			LOG_ERROR("Shader cannot be linked...");
		}
	}
}