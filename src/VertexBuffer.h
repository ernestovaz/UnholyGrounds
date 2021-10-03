#pragma once

class VertexBuffer
{
private:
    unsigned int bufferID; //internal opengl buffer id
public:
    VertexBuffer(const void* data, unsigned int size); 
    ~VertexBuffer();

    void Bind();
    void Unbind();

};
