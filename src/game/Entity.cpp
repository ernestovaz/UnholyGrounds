#include "Entity.h"

#include <vector>
#include <iostream>

Entity::Entity(Model model, glm::mat4 initialMatrix) : model(model), matrix(initialMatrix)
{
}

Entity::Entity(std::string name, bool hasBoundingBox, glm::mat4 initialMatrix) 
    : model(name, hasBoundingBox), matrix(initialMatrix)
{
}

Entity::Entity(std::string name, BoundingBox boundingBox, glm::mat4 initialMatrix) 
    : model(name, false), matrix(initialMatrix)
{
    this->model.setBoundingBox(boundingBox);
}

Entity::Entity()
{
}

BoundingBox Entity::getGlobalBoundingBox()
{
    BoundingBox local = this->model.getBoundingBox();
    std::vector<glm::vec4> global;
    for(glm::vec4 point : local.boundingBox)
    {
        global.push_back(this->matrix * point);
    }
    return BoundingBox(global);
}
