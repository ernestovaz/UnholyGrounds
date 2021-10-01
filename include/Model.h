#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <stdexcept>

#include <tiny_obj_loader.h>

class Model
{
public: //initially

    tinyobj::attrib_t           attrib;     // vertex data
    std::vector<tinyobj::shape_t>       shapes;     // index data
    std::vector<tinyobj::material_t> materials;
    
    Model(const char* filename, const char* basepath, bool triangulate);
};      

#endif        
