#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Enemy.h"

Enemy::Enemy()
{
    position = glm::vec4(2.0f, 3.0f, 4.0f, 1.0f);
    facing   = glm::vec4(1.0f, 2.0f, 0.0f,  0.0f);
    speed = 0.15f;
    health = 100;
}


