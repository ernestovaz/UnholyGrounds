#pragma once

#include <glm/vec3.hpp>

#include "Model.h"

class Entity
{
public:
    glm::vec3 pos;
    glm::vec3 rot;
    Model   model;
    Entity(Model model, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f)); 
};
