#pragma once

#include<string>

#include "Entity.h"
#include "Actor.h"
#include "FrameBuffer.h"

class Renderer
{
public: 
    Renderer(float screenRatio);
    ~Renderer();
    void draw(Actor player);
    void drawEntity(Entity entity);
    void drawPlayer(Entity playerEntity);

private:
    Entity playerEntity;
    Entity testEntity;

    float screenRatio;

    FrameBuffer lowResBuffer;

    unsigned int firstPassShaderId;
    unsigned int secondPassShaderId;

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

