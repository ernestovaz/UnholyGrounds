#pragma once

#include <glad/glad.h>
#include <signal.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);     //stops execution (gcc)
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))   
//macros for printing opengl errors, for easier debugging

void GLClearError();
bool GLLogCall(const char* func, const char* file, int line);
