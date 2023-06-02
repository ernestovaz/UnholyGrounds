#pragma once

#include <glm/mat4x4.hpp>
#include <string.h>

#include "BoundingBox.h"
#include "../renderer/Model.h"

class Entity
{
public:
    Model       model;
    glm::mat4   matrix;
    Entity(Model model, glm::mat4 initialMatrix = glm::mat4(1.0f)); 
    Entity(std::string name, bool hasBoundingBox, glm::mat4 initialMatrix = glm::mat4(1.0f)); 
    Entity(std::string name, BoundingBox boundingBox, glm::mat4 initialMatrix = glm::mat4(1.0f)); 
    Entity(); 

    BoundingBox getGlobalBoundingBox();
};
