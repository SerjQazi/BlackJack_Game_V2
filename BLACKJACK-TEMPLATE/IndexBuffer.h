#pragma once

#include "pch.h"
#include "OpenGLBuffer.h"

class IndexBuffer : public OpenGLBuffer
{
public:
	IndexBuffer() : OpenGLBuffer(GL_ELEMENT_ARRAY_BUFFER) { }
};