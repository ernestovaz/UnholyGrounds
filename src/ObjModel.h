#pragma once

#include <vector>
#include <stdexcept>

#include <tiny_obj_loader.h>

class ObjModel
{
public: //initially

    tinyobj::attrib_t           attrib;             // vertex data
    std::vector<tinyobj::shape_t>       shapes;     // index data
    std::vector<tinyobj::material_t> materials;
    
    ObjModel(const char* filename, const char* basepath, bool triangulate);
};      

