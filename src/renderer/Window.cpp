#include <cstdlib>
#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    this->window = glfwCreateWindow(screen->width, screen->height, "window", monitor, NULL);
    this->screenRatio = (float)screen->width/(float)screen->height;

    if (!this->window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->window);
    glfwSetWindowUserPointer(this->window, input);
    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mod)
    {
        auto input = (InputManager*)glfwGetWindowUserPointer( window );
        input->keyCallback(key, action, mod); 
    });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos)
    {
        auto input = (InputManager*)glfwGetWindowUserPointer( window );
        input->cursorCallback(xpos, ypos); 
    });
    double xpos,ypos;
    glfwGetCursorPos(this->window, &xpos, &ypos);
    input->setInitialCursorPos(xpos, ypos);

    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });


    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
   glfwDestroyWindow(this->window); 
   glfwTerminate();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Window::setShouldClose()
{
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(this->window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

float Window::getScreenRatio()
{
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    return (float)width/(float)height;
}
