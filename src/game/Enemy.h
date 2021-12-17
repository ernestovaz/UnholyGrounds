#pragma once 

#include <glm/vec4.hpp>

#include "Actor.h"

class Enemy : public Actor
{
private:
public:
    static const glm::vec4 HEAD_SPHERE_ORIGIN;
    static const float HEAD_SPHERE_RADIUS;
    Enemy();
};
