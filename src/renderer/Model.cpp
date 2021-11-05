#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <tiny_obj_loader.h>

#include <cstdio>
#include <cassert>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <stdexcept>

#include "Model.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "utils.h"

Model::Model(std::string name)
{
    std::string filename = "data/models/"+name+".obj";
    std::vector<tinyobj::material_t> materials; //unused for now    
    std::vector<tinyobj::shape_t> shapes;
    std::string err;
    tinyobj::attrib_t   attrib;

    //Loads model from filename
    //Based on example from https://github.com/tinyobjloader/tinyobjloader
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), NULL, true);
    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());
    if (!ret)
        throw std::runtime_error("Erro ao carregar modelo.");

    std::vector<GLuint> indices;
    std::vector<float> model_coefficients;
    std::vector<float> normal_coefficients;
    std::vector<float> texture_coefficients;

    bool fileHasNormals = false;
    //bool fileHasTexture = false;
    
    for (size_t shape = 0; shape < shapes.size(); ++shape) 
    // a single .obj can have multiple "shapes" (e.g. each shape can have a diferent material)
    {
        size_t first_index = indices.size();
        size_t num_triangles = shapes[shape].mesh.num_face_vertices.size();
        for (size_t triangle = 0; triangle < num_triangles; ++triangle) 
        // each line in .obj represents a polygon face, in this case a triangle
        {
            assert(shapes[shape].mesh.num_face_vertices[triangle] >= 3);
            for (size_t vertex = 0; vertex < 3; ++vertex)               
            //each triangle has three vertices 
            {
                tinyobj::index_t idx = shapes[shape].mesh.indices[3*triangle + vertex];
                indices.push_back(first_index + 3*triangle + vertex);
                const float vx = attrib.vertices[3*idx.vertex_index + 0];
                const float vy = attrib.vertices[3*idx.vertex_index + 1];
                const float vz = attrib.vertices[3*idx.vertex_index + 2];

                model_coefficients.push_back( vx ); 
                model_coefficients.push_back( vy ); 
                model_coefficients.push_back( vz ); 
                model_coefficients.push_back( 1.0f ); 
                
                if ( idx.normal_index != -1 )
                //checks if model has normal coefficients
                {
                    fileHasNormals = true;
                    const float nx = attrib.normals[3*idx.normal_index + 0];
                    const float ny = attrib.normals[3*idx.normal_index + 1];
                    const float nz = attrib.normals[3*idx.normal_index + 2];
                    normal_coefficients.push_back( nx ); // X
                    normal_coefficients.push_back( ny ); // Y
                    normal_coefficients.push_back( nz ); // Z
                    normal_coefficients.push_back( 0.0f ); // W
                }

                if ( idx.texcoord_index != -1 )
                //checks if model has texture coordinates
                {
                    //fileHasTexture = true;
                    const float u = attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = attrib.texcoords[2*idx.texcoord_index + 1];
                    texture_coefficients.push_back( u );
                    texture_coefficients.push_back( v );
                }
            
            }
        }
    }
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    VertexBuffer positions(model_coefficients.data(), model_coefficients.size()*sizeof(float), 0, 4);
    if(!fileHasNormals) 
        throw std::runtime_error("Modelo não possui normais");
    VertexBuffer normals(normal_coefficients.data(), normal_coefficients.size()*sizeof(float), 1, 4);
    VertexBuffer textures(texture_coefficients.data(), texture_coefficients.size()*sizeof(float), 2, 2);
    IndexBuffer indexBufferObject(indices.data(), indices.size());


    this->name              = name; 
    this->indexCount        = indices.size(); 
    this->renderingMode     = GL_TRIANGLES; 
    this->vaoID             = vaoID;
    this->vertexPositions   = positions;
    this->vertexNormals     = normals;
    this->vertexTextures    = textures;
    this->indices           = indexBufferObject;
    this->textureID         = loadTexture();

    glBindVertexArray(0);
}

Model::Model()
{
}

unsigned int Model::getId()
{
    return this->vaoID;
}

size_t Model::getIndexCount()
{
    return this->indexCount;
}

unsigned int Model::loadTexture()
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    std::string filename = "data/textures/"+this->name+".png";
    unsigned char *textureData = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!textureData)
    {
        std::cout << "No texture found for " + this->name + ".\n";
        textureData = stbi_load("src/data/textures/error.png", &width, &height, &channels, 0);
    }

    unsigned int textureId;
    GLCall(glGenTextures(1, &textureId));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureId));
    GLCall(glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, textureData));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(textureData);

    return textureId;
}

unsigned int Model::getTextureId()
{
    return this->textureID;
}

unsigned int Model::getRenderingMode()
{
    return this->renderingMode;
}
