#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <stdexcept>

#include <tiny_obj_laoder.h>

class Model
{
public: //initially

    private tinyobj::attrib_t           attrib;     // vertex data
    std::vector<tinyobj::shape_t>       shapes;     // index data
    
    Model(const char* filename, const char* basepath = NULL, bool triangulate = true);
}

        
