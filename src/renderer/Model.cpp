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

Model::Model(std::string name, size_t first_index, size_t num_indices, GLenum rendering_mode) //deprecated constructor
{
    this->name = name;
    this->first_index = first_index;
    this->num_indices = num_indices;
    this->rendering_mode = rendering_mode;
}

Model::Model(std::string filename)
{
    //Loads model from filename
    //Based on example from https://github.com/tinyobjloader/tinyobjloader
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
    std::vector<float> normal_coefficients;
    std::vector<float> texture_coefficients;
    
    for (size_t shape = 0; shape < shapes.size(); ++shape) // a single .obj can have multiple "shapes" (e.g. each shape can have a diferent material)
    {
	size_t first_index = indices.size();
	size_t num_triangles = shapes[shape].mesh.num_face_vertices.size();
	for (size_t triangle = 0; triangle < num_triangles; ++triangle) // each line in .obj represents a polygon face, in this case a triangle
	{
            assert(shapes[shape].mesh.num_face_vertices[triangle] >= 3);
	    for (size_t vertex = 0; vertex < 3; ++vertex)                //each triangle has three vertices 
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
		
		//testa se existem normais e texturas no ObjModel, lendo em caso afirmativo
		if ( idx.normal_index != -1 )
                {
                    const float nx = attrib.normals[3*idx.normal_index + 0];
                    const float ny = attrib.normals[3*idx.normal_index + 1];
                    const float nz = attrib.normals[3*idx.normal_index + 2];
                    normal_coefficients.push_back( nx ); // X
                    normal_coefficients.push_back( ny ); // Y
                    normal_coefficients.push_back( nz ); // Z
                    normal_coefficients.push_back( 0.0f ); // W
                }

                if ( idx.texcoord_index != -1 )
                {
                    const float u = attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = attrib.texcoords[2*idx.texcoord_index + 1];
                    texture_coefficients.push_back( u );
                    texture_coefficients.push_back( v );
                }
		
	    }
	}

    this->name                  = shapes[shape].name; //the name is set as the last shape's name. needs changing
    this->first_index           = 0; 
    this->num_indices           = indices.size(); 
    this->rendering_mode        = GL_TRIANGLES;       //in this method we insert data into indices in the template of GL_TRIANGLES  
    this->indices               = indices;
    this->vertex_positions      = model_coefficients;   //right now, all shapes go into same model, it's useful to separate shapes for animations,
                                                        //however it's probably not urgent 
    }
}
