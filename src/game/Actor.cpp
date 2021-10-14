#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Actor.h"

Actor::moveForward()
{
    glm::vec3 forward(facing);
    position += glm::normalize(forward);
}

Actor::moveBackward()
{
    glm::vec3 backward(-facing);
    position += glm::normalize(backward);
}

Actor::moveLeft()
{
    glm::vec3 forward(facing);
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 homogenousLeft(left, 0.0f);
    position += homogenousLeft*0.01f;
}

Actor::moveRight()
{
    glm::vec3 backward(-facing);
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 homogenousRight(right, 0.0f);
    position += homogenousRight*0.01f;
}
