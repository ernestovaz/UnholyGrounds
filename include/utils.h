#pragma once

#include <glad/glad.h>
#include <signal.h>
#include <cstdio>
#include <iostream>

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* func, const char* file, int line)
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

static GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        const char* error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "UNKNOWN"; break;
        }
        fprintf(stderr, "ERROR: OpenGL \"%s\" in file \"%s\" (line %d)\n", error, file, line);
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__)
#define ASSERT(x) if (!(x)) raise(SIGTRAP);     //macro to stop execution (gcc)
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))   
