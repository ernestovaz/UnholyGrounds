#include "ObjModel.h"


ObjModel::ObjModel(const char* filename, const char* basepath = NULL, bool triangulate = true)
{
    std::string err;
    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

    if(!success)
        throw std::runtime_error("Erro ao carregar modelo.");
}
