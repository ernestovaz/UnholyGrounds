#pragma once

#include<string>

#include "Entity.h"
#include "Actor.h"
#include "FrameBuffer.h"

class Renderer
{
public: 
    Renderer(std::string vertexShader, std::string fragmentShader, float screenRatio);
    ~Renderer();
    void draw(Actor player);
    void drawEntity(Entity entity);
    void drawPlayer(Entity playerEntity);

private:
    Entity playerEntity;
    Entity testEntity;

    float screenRatio;

    FrameBuffer lowResBuffer;

    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;
    unsigned int framebufferId;
    unsigned int shaderProgramId;

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

