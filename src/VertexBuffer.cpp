#include <glad/glad.h>

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID)); 
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); 

}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void VertexBuffer::Bind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void VertexBuffer::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
