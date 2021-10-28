#pragma once
   
#include <GLFW/glfw3.h>

#include "InputManager.h"

class Window
{
private:
    GLFWwindow* window;
    float screenRatio;
public:
    unsigned int width;
    unsigned int height;

    Window(InputManager* input);
    ~Window();

    bool shouldClose();
    void setShouldClose();
    void swapBuffers();
    void pollEvents();
};
