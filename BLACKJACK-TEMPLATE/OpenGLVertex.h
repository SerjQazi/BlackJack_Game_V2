#pragma once

class OpenGLVertex
{
public:
	OpenGLVertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoord)
		: position(position), color(color), texCoord(texCoord)
	{ }

	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
};