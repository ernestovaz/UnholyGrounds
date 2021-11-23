#include "Entity.h"

Entity::Entity(Model model, glm::mat4 initialMatrix) : model(model), matrix(initialMatrix)
{
}

Entity::Entity(std::string name, glm::mat4 initialMatrix) : model(name), matrix(initialMatrix)
{
}

Entity::Entity()
{
}
