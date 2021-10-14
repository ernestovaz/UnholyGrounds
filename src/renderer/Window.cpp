#include <cstdlib>
#include <cstdio>

#include <GLFW/glfw33.h>

#include "Window.h"
#include "InputManager.h"

Window::Window(InputManager* input)
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
        input->callback(key, action, mod); 
    });
}
