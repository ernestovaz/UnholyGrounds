#include "Entity.h"

Entity::Entity(Model model, glm::mat4 initialMatrix) : model(model), matrix(initialMatrix)
{
}

Entity::Entity(std::string name, bool hasBoundingBox, glm::mat4 initialMatrix) 
    : model(name, hasBoundingBox), matrix(initialMatrix)
{
}

Entity::Entity()
{
}
