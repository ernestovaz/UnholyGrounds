#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Actor.h"

#define SPEED 0.05f
#define SENSITIVITY 0.002f
#define PI 3.141592f/2.0f

Actor::Actor()
{
    position = glm::vec4(0.0f, 1.0f, -5.5f, 1.0f);
    facing   = glm::vec4(0.0f, 0.0f, 1.0f,  0.0f);
    viewYaw  = 0.0f;
    viewPitch= 0.0f;
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
    forward.y = 0;
    glm::vec4 hmForward(glm::normalize(forward), 0.0f);
    position += hmForward * SPEED;
}

void Actor::moveBackward()
{
    glm::vec3 backward(-facing);
    backward.y = 0;
    glm::vec4 hmBackward(glm::normalize(backward), 0.0f);
    position += hmBackward * SPEED;
}

void Actor::moveLeft()
{
    glm::vec3 forward(facing);
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 hmLeft(left, 0.0f);
    position += hmLeft * SPEED;
}

void Actor::moveRight()
{
    glm::vec3 backward(-facing);
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 hmRight(right, 0.0f);
    position += hmRight * SPEED;
}

void Actor::moveView(float dx, float dy)
{
    viewYaw   -= SENSITIVITY * dx; 
    viewPitch -= SENSITIVITY * dy; 
    if(viewPitch > PI/2)
        viewPitch = PI/2;
    if(viewPitch < -PI/2)
        viewPitch = -PI/2;
    facing = glm::vec4(
            glm::cos(viewPitch) * glm::sin(viewYaw),
            glm::sin(viewPitch),
            glm::cos(viewPitch) * glm::cos(viewYaw),
            0.0f
    );
}
