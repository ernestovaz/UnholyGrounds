#pragma once

#include<cstdio>
#include<string>
#include<vector>

// Abstraction for any 3d model to be rendered on screen.
// Now holds info necessary to call glDraw, ideally it should only hold pointer to its VAO, in order to pass it to a high level draw function.

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
    Model(std::string name, size_t first_index, size_t run_indices, GLenum rendering_mode); // Deprecated constructor
    Model(std::string filename); // Should in the future be the main constructor, reads model from file
};
