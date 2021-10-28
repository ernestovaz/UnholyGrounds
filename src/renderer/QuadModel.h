#pragma once

//creates a quad given a texture id, for content to be rendered into it

#include "Model.h"

class QuadModel : public Model
{
public:
    QuadModel(std::string name, unsigned int textureId);

};
