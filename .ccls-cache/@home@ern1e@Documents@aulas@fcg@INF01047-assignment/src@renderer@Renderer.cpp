#include <iostream>
#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line)
{
    bool foundError = true;
    while(GLenum error = glGetError()) 
    {
        std::cout << "(!)OpenGL Error number " << error <<
            " in " << func << ", " << file << " at line " <<
            line << std::endl;
        foundError = false;
    }

    return foundError;
} 
