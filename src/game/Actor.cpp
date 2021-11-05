#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Actor.h"

#define SENSITIVITY 0.002f
#define PI 3.141592f/2.0f

Actor::Actor()
{
    position = glm::vec4(0.0f, 3.0f, 0.0f, 1.0f);
    facing   = glm::vec4(0.0f, 0.0f, 1.0f,  0.0f);
    speed = 0.10f;
    health = 100;
    ammunition = 50;
    viewYaw  = 0.0f;
    viewPitch= 0.0f;
    isCrouched = false;
    isWalking = false;
    infAmmunition = false;
}

glm::vec4 Actor::getPosition()
{
    if(isCrouched){
        isCrouched = false;
        return position - glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    }
    else{
        return position;
    }
}

glm::vec4 Actor::getFacing()
{
    return facing;
}

float Actor::getSpeed()
{
    if (isWalking){
        isWalking = false;
        return speed - 0.05f;
    }
    else{
        return speed;
    }
    
}

int Actor::getHealth()
{
    return health;
}

int Actor::getAmmunition()
{
    if (infAmmunition){
        return 9999;
    }
    else{
        return ammunition;
    }
}

void Actor::setInfAmmunition()
{
    infAmmunition = true;
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

void Actor::moveWalk()
{
    isWalking = true;
}

void Actor::crouch()
{
    isCrouched = true;
    isWalking = true;
}

void Actor::shoot()
{
    ammunition--;
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
