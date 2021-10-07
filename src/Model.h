#pragma once

#include<cstdio>
#include<string>
#include<vector>


class Model
{
public: //initially
    std::string  name;        
    size_t       first_index; 
    size_t       num_indices; 
    GLenum       rendering_mode; 
    std::vector<GLuint> indices;
    std::vector<float> vertex_positions;

    Model();
    Model(std::string name, size_t first_index, size_t run_indices, GLenum rendering_mode);
    Model(std::string filename);
};
