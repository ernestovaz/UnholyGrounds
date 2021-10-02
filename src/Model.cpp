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

