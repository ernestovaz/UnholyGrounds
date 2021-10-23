#pragma once

#include <glm/vec4.hpp>

#include "Model.h"

class Entity
{
public:
    glm::vec3 pos;
    Model   model;
    Entity(Model model);
    Entity(Model model, glm::vec3 position); 
};
