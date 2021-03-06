#pragma once

//Abstraction for a VBO, may hold array of positions, normals, color coordinates, etc.

class VertexBuffer
{
private:
    unsigned int bufferID; //internal opengl buffer id
public:
    VertexBuffer(const void* data, unsigned int size, int location, int dimensions); 
    VertexBuffer();
    ~VertexBuffer();

    void Bind();
    void Unbind();
};
