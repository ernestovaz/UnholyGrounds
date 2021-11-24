#pragma once

#include<string>

#include "Entity.h"
#include "Model.h"
#include "Player.h"
#include "FrameBuffer.h"
#include "Scene.h"

class Renderer
{
public: 
    Renderer(unsigned int screenWidth, unsigned int screenHeight);
    ~Renderer();
    void draw(Scene& scene);

private:
    FrameBuffer downscaledBuffer; 
    //buffer with lower resolution than the screen, the game is rendered into this buffer 
    //in order to achieve a pixelated effect

    Model* screenQuad; 
    Model* crosshair; 
    //quad that covers the whole screen, the lower resolution rendered output is mapped into it

    float screenWidth;
    float screenHeight;

    float fov;

    unsigned int shader3dId;     //first shader, used for normal rendering, 
                                        //which is then bound to a texture

    unsigned int shader2dId;    //second shader, used for rendering from a texture
                                        //also used for ui elements

    unsigned int modelUniformId;
    unsigned int viewUniformId;
    unsigned int projectionUniformId;
    unsigned int lightingUniformId;
    unsigned int handUniformId;
    unsigned int groundUniformId;
    unsigned int camPosUniformId;
    unsigned int camDirUniformId;
    unsigned int modelUniform2dId;

    void drawEntity(Entity entity);
    void drawModel(Model model);
    void drawPlayer(Entity playerEntity);
    void drawUI(Model uiElement);
    void renderTextureToScreen();       //render texture input into the entire screen

    void calculateShootingAnimation(Player& player);

    unsigned int LoadVertexShader(std::string name);   
    unsigned int LoadFragmentShader(std::string name);
    void LoadShader(const char* filename, unsigned int shader_id);
    unsigned int CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId); 
};

