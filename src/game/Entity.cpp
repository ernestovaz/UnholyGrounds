#include "Entitiy.h"

Entity::Entity(Model model) : model(model)
{
}

Entity::Entity(Model model, glm::vec3 position) : model(model), pos(position)
{
}
