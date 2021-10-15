#pragma once
   
#include <GLFW/glfw3.h>

#include "InputManager.h"

class Window
{
private:
    GLFWwindow* window;
    float screenRatio;
public:
    Window(InputManager* input);
    ~Window();
    bool shouldClose();
    void closeWindow();
    void swapBuffers();
    void pollEvents();
    float getScreenRatio();
};
