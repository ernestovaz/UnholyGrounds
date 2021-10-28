#pragma once

#include<string>

#include "Entity.h"
#include "Model.h"
#include "Actor.h"
#include "FrameBuffer.h"

class Renderer
{
public: 
    Renderer(float screenRatio);
    ~Renderer();
    void draw(Actor player);

private:
    FrameBuffer downscaledBuffer;

    Entity playerEntity;
    Entity groundEntity;

    Model* screenQuad;

    float screenRatio;

    unsigned int firstPassShaderId;
    unsigned int secondPassShaderId;

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;

    void drawEntity(Entity entity);
    void drawModel(Model model);
    void drawPlayer(Entity playerEntity);
    void renderTextureToScreen();

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

