#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line)
{
    bool foundError = false;
    while(GLenum error = glGetError()) 
    {
        std::cout << "(!)OpenGL Error number " << error <<
            " in " << func << ", " << file << " at line " <<
            line << std::endl;
        foundError = true;
    }

    return foundError;
} 
