#pragma once

#include<cstdio>
#include<string>
#include<vector>
#include<GLFW/glfw3.h>


class Model
{
public: //initially
    std::string  name;        
    size_t       first_index; 
    size_t       num_indices; 
    GLenum       rendering_mode; 

    Model();
    Model(std::string name, size_t first_index, size_t run_indices, GLenum rendering_mode);
};
