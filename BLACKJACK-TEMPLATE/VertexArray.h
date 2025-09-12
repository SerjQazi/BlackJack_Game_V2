#pragma once

#include "GameConfiguration.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

private:
    GLuint VAO;
};