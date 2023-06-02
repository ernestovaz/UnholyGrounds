#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "Enemy.h"

const glm::vec4 Enemy::HEAD_SPHERE_ORIGIN = glm::vec4(-0.021464f, 3.75f, 0.0f, 1.0f); //glm::vec4(-0.021464f, 1.8665096f, 0.0f, 1.0f); 
const float     Enemy::HEAD_SPHERE_RADIUS = 0.37; //0.125707; 

Enemy::Enemy(Entity entity, glm::vec4 position, glm::vec4 facing)
{
    this->position = position;
    this->facing = facing;
    this->entity = entity;
    speed = 0.15f;
    health = 100;
}


