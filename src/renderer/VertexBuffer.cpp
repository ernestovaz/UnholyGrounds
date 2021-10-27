#include <glad/glad.h>

#include "VertexBuffer.h"
#include "utils.h"

VertexBuffer::VertexBuffer()
{
}
VertexBuffer::VertexBuffer(const void* data, unsigned int size, int location, int dimensions)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID)); 
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));   
    GLCall(glVertexAttribPointer(location, dimensions, GL_FLOAT, GL_FALSE, 0, 0)); 
    GLCall(glEnableVertexAttribArray(location)); 
}

VertexBuffer::~VertexBuffer()
{
    //GLCall(glDeleteBuffers(1, &bufferID));
}

void VertexBuffer::Bind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void VertexBuffer::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

