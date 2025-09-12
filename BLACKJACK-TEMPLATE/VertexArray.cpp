#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray() 
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

VertexArray::~VertexArray() 
{
    glDeleteVertexArrays(1, &VAO);
}

void VertexArray::bind() const 
{
    glBindVertexArray(VAO);
}

void VertexArray::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}