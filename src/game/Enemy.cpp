#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "Enemy.h"

const glm::vec4 Enemy::HEAD_SPHERE_ORIGIN = glm::vec4(-0.021464f, 1.8665096f, 0.0f, 1.0f); 
const float     Enemy::HEAD_SPHERE_RADIUS = 0.125707; 

Enemy::Enemy()
{
    position = glm::vec4(2.0f, 3.0f, 4.0f, 1.0f);
    facing   = glm::vec4(1.0f, 2.0f, 0.0f,  0.0f);
    speed = 0.15f;
    health = 100;
}


