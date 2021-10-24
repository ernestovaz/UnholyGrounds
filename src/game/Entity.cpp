#include "Entity.h"

Entity::Entity(Model model, glm::mat4 initialMatrix) : model(model), matrix(initialMatrix)
{
}

Entity::Entity()
{
}
