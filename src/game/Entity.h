#pragma once

#include <glm/mat4x4.hpp>
#include <string.h>

#include "Model.h"

class Entity
{
public:
    Model       model;
    glm::mat4   matrix;
    Entity(Model model, glm::mat4 initialMatrix = glm::mat4(1.0f)); 
    Entity(std::string name, glm::mat4 initialMatrix = glm::mat4(1.0f)); 
    Entity(); 
};
