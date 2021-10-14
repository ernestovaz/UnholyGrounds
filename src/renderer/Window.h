#pragma once
   
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* window;
public:
    Window();
    ~Window();
    bool shouldClose();
    void swapBuffers();
    GLFWwindow* getGLFWwindow();

}
