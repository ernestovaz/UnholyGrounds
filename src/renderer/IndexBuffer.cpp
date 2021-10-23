#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::IndexBuffer(const GLuint* data, unsigned int index_count)
{
    count = index_count;
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID)); 
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW)); 
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void IndexBuffer::Bind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
}

void IndexBuffer::Unbind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
