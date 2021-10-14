#pragma once
   
#include <GLFW/glfw3.h>

#include "InputManager.h"

class Window
{
private:
    GLFWwindow* window;
public:
    Window(InputManager* input);
    ~Window();
    bool shouldClose();
    void swapBuffers();
    GLFWwindow* getGLFWwindow();

}
