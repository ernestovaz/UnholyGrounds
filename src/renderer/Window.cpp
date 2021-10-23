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
    //glfw initialization

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* screen = glfwGetVideoMode(monitor);
    this->window = glfwCreateWindow(screen->width, screen->height, "window", monitor, NULL);
    this->screenRatio = (float)screen->width/(float)screen->height;
    //gets screen configuration and creates fullscreen window

    if (!this->window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->window);
    //creates glfw context

    glfwSetWindowUserPointer(this->window, input); //sets input manager pointer, for handling callbacks
    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mod)
    {
        auto input = (InputManager*)glfwGetWindowUserPointer( window );
        input->keyCallback(key, action, mod); 
    });
    //lambda used for callbacks (calls input manager for handling)

    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos)
    {
        auto input = (InputManager*)glfwGetWindowUserPointer( window );
        input->cursorCallback(xpos, ypos); 
    });
    //lambda used for callbacks (calls input manager for handling)
    
    double xpos,ypos;
    glfwGetCursorPos(this->window, &xpos, &ypos);
    input->setInitialCursorPos(xpos, ypos);
    //sets initial position for mouse, since movement is calculated from mouse displacement

    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
    //lambda used for callbacks, just updates ratio


    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    //if possible, uses raw input, for better aim control

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //hides mouse cursor
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
