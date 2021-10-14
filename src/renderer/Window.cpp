#include <cstdlib>
#include <cstdio>

#include <GLFW/glfw33.h>

#include "Window.h"

Window::Window()
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback([](int error, const char* description) // lambda function
    {
        fprintf(stderr, "ERROR: GLFW: %s\n", description);
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* screen = glfwGetVideoMode(monitor);
    g_ScreenRatio = screen->width/screen->height;

    this->window = glfwCreateWindow(screen->width, screen->height, "window", monitor, NULL);

    if (!this->window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->window);

    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mod)
    {
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);  //IMPLEMENT INTO COMMAND

        if (key == GLFW_KEY_W && action == GLFW_PRESS)
        {
            g_WPressed = true;
        }
        if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        {
            g_WPressed = false;
        }

        if (key == GLFW_KEY_S && action == GLFW_PRESS)
        {
            g_SPressed = true;
        }
        if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        {
            g_SPressed = false;
        }

        if (key == GLFW_KEY_A && action == GLFW_PRESS)
        {
            g_APressed = true;
        }
        if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        {
            g_APressed = false;
        }

        if (key == GLFW_KEY_D && action == GLFW_PRESS)
        {
            g_DPressed = true;
        }
        if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        {
            g_DPressed = false;
        }
    });

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

}
