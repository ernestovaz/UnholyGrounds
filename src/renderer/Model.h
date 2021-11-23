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
protected:
    std::string     name;
    size_t          indexCount; 
    unsigned int    renderingMode;
    unsigned int    vaoID;
    VertexBuffer    vertexPositions;
    IndexBuffer     indices;
    VertexBuffer    vertexTextures;
    unsigned int    textureID;

    unsigned int loadTexture(std::string filename, bool hasAlpha);

private:
    VertexBuffer    vertexNormals;

public: 
    Model(std::string name, bool hasAlpha = true); 
    Model();
    unsigned int getId();
    unsigned int getTextureId();
    unsigned int getRenderingMode();
    size_t getIndexCount();
    void draw();
};
