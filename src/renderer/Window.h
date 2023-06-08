#pragma once
   
#include "../input/InputManager.h"

#include <GLFW/glfw3.h>


class Window
{
private:
    GLFWwindow* window;
    float screenRatio;

public:
    unsigned int width;
    unsigned int height;

    Window();
    ~Window();

    void setKeyCallbacks(InputManager* input);
    bool shouldClose();
    void setShouldClose();
    void swapBuffers();
    void pollEvents();
    
    //TODO: fix this 
    GLFWwindow* getThing() { return window; };
};
