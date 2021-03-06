#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Actor.h"

Actor::Actor()
{
    position = glm::vec4(0.0f, 3.0f, 0.0f, 1.0f);
    facing   = glm::vec4(0.0f, 0.0f, 1.0f,  0.0f);
    speed = 0.10f;
    health = 100;
}

glm::vec4 Actor::getPosition()
{
    return position;
}

glm::vec4 Actor::getFacing()
{
    return facing;
}

float Actor::getSpeed()
{
    return speed;   
}

int Actor::getHealth()
{
    return health;
}

void Actor::moveForward()
{
    glm::vec3 forward(facing);
    forward.y = 0;
    glm::vec4 hmForward(glm::normalize(forward), 0.0f);
    position += hmForward * getSpeed();
}

void Actor::moveBackward()
{
    glm::vec3 backward(-facing);
    backward.y = 0;
    glm::vec4 hmBackward(glm::normalize(backward), 0.0f);
    position += hmBackward * getSpeed();
}

void Actor::moveLeft()
{
    glm::vec3 forward(facing);
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 hmLeft(left, 0.0f);
    position += hmLeft * getSpeed();
}

void Actor::moveRight()
{
    glm::vec3 backward(-facing);
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 hmRight(right, 0.0f);
    position += hmRight * getSpeed();
}

