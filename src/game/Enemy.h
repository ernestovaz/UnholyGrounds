#pragma once 

#include <glm/vec4.hpp>

#include "Actor.h"
#include "Entity.h"

class Enemy : public Actor
{
private:
public:
    Entity entity;
    static const glm::vec4 HEAD_SPHERE_ORIGIN;
    static const float HEAD_SPHERE_RADIUS;
    Enemy(Entity entity, glm::vec4 position, glm::vec4 facing);
};
