#pragma once

#include<cstdio>
#include<string>
#include<vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

// Abstraction for any 3d model to be rendered on screen.
// Now holds info necessary to call glDraw, ideally it should only hold pointer to its VAO, in order to pass it to a high level draw function.

class Model
{
private:
    std::string     name;
    size_t          indexCount; 
    unsigned int    vaoID;
    VertexBuffer    vertexPositions;
    VertexBuffer    vertexNormals;
    IndexBuffer     indices;

public: 
    Model(std::string name); 
    unsigned int getId();
    size_t getIndexCount();
    void draw();
};
