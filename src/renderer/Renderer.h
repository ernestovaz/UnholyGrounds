#pragma once

#include<string>

#include "Entity.h"
#include "Actor.h"

class Renderer
{
public: 
    Renderer(std::string vertexShader, std::string fragmentShader, float screenRatio);
    ~Renderer();
    void draw(Actor player);
    void drawEntity(Entity entity);

private:
    Entity playerEntity;
    Entity testEntity;

    float screenRatio;

    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;
    unsigned int shaderProgramId;

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

