#pragma once

#include<string>

#include "Entity.h"
#include "Model.h"
#include "Actor.h"
#include "FrameBuffer.h"

class Renderer
{
public: 
    Renderer(unsigned int screenWidth, unsigned int screenHeight);
    ~Renderer();
    void draw(Actor player);

private:
    FrameBuffer downscaledBuffer; 
    //buffer with lower resolution than the screen, the game is rendered into this buffer 
    //in order to achieve a pixelated effect

    Entity playerEntity;
    Entity groundEntity;

    Model* screenQuad; 
    //quad that covers the whole screen, the lower resolution rendered output is mapped into it

    float screenWidth;
    float screenHeight;

    unsigned int firstPassShaderId;     //first shader, used for normal rendering, 
                                        //which is then bound to a texture

    unsigned int secondPassShaderId;    //second shader, used for rendering from a texture
                                        //may also be used for more post-processing effects

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;

    void drawEntity(Entity entity);
    void drawModel(Model model);
    void drawPlayer(Entity playerEntity);
    void renderTextureToScreen();       //render texture input into the entire screen

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

