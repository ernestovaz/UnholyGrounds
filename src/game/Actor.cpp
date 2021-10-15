#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Actor.h"

Actor::Actor()
{
    position = glm::vec4(0.0f, 1.0f, -5.5f, 1.0f);
    facing   = glm::vec4( 0.0f, 0.0f, 1.0f,  0.0f);
}

glm::vec4 Actor::getPosition()
{
    return position;
}

glm::vec4 Actor::getFacing()
{
    return facing;
}

void Actor::moveForward()
{
    glm::vec3 forward(facing);
    glm::vec4 hmForward(glm::normalize(forward), 0.0f);
    position += hmForward;
}

void Actor::moveBackward()
{
    glm::vec3 backward(-facing);
    glm::vec4 hmBackward(glm::normalize(backward), 0.0f);
    position += hmBackward;
}

void Actor::moveLeft()
{
    glm::vec3 forward(facing);
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 hmLeft(left, 0.0f);
    position += hmLeft*0.01f;
}

void Actor::moveRight()
{
    glm::vec3 backward(-facing);
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 hmRight(right, 0.0f);
    position += hmRight*0.01f;
}
