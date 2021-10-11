#pragma once

#include <glad/glad.h>
#include <signal.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);     //macro to stop execution (gcc)
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))   
//macros for printing opengl errors, for easier debugging
//clear all errors before calling function, calls it, and in case of error raises SIGTRAP printing error

void GLClearError();
bool GLLogCall(const char* func, const char* file, int line);
