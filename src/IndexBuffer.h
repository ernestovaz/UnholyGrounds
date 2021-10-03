#pragma once

class IndexBuffer
{
private:
    unsigned int bufferID; //internal opengl buffer id
    unsigned int count;
public:
    IndexBuffer(const GLuint* data, unsigned int count); 
    ~IndexBuffer();

    void Bind();
    void Unbind();

    inline unsigned int GetCount() const { return count; }
};
