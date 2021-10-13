#include <tiny_obj_loader.h>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <glad/glad.h>
#include <stdexcept>

#include "Model.h"

Model::Model()
{

}

Model::Model(std::string name, size_t first_index, size_t num_indices, GLenum rendering_mode)
{
    this->name = name;
    this->first_index = first_index;
    this->num_indices = num_indices;
    this->rendering_mode = rendering_mode;
}

Model::Model(std::string filename)
{
    std::vector<tinyobj::material_t> materials; //unused for now    
    tinyobj::attrib_t   attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), NULL, true);
    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());
    if (!ret)
        throw std::runtime_error("Erro ao carregar modelo.");

    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;

    for (size_t shape = 0; shape < shapes.size(); ++shape)
    {
	size_t first_index = indices.size();
	size_t num_triangles = shapes[shape].mesh.num_face_vertices.size();
	for (size_t triangle = 0; triangle < num_triangles; ++triangle)
	{
            assert(shapes[shape].mesh.num_face_vertices[triangle] >= 3);
	    for (size_t vertex = 0; vertex < 3; ++vertex)
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
	    }
	}

    this->name                  = shapes[shape].name;
    this->first_index           = 0; 
    this->num_indices           = indices.size(); 
    this->rendering_mode        = GL_TRIANGLES;       
    this->indices               = indices;
    this->vertex_positions      = model_coefficients;
    }
}
