#pragma once

#include <glad/glad.h>

//Abstraction for buffer that holds index arrays.

class IndexBuffer
{
private:
    unsigned int bufferID; //internal opengl buffer id
    unsigned int count;
public:
    IndexBuffer(const GLuint* data, unsigned int count); 
    IndexBuffer();
    ~IndexBuffer();

    void Bind();
    void Unbind();

    inline unsigned int GetCount() const { return count; }
};
