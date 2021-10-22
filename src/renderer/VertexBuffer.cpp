#include <glad/glad.h>

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, int id)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID)); 
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));   
    GLCall(glVertexAttribPointer(id, 4, GL_FLOAT, GL_FALSE, 0, 0)); //assuming we're only going to work with 3D.
    GLCall(glEnableVertexAttribArray(id)); 
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
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
