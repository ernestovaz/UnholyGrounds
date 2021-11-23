#include "Player.h"

#include <glm/trigonometric.hpp>

#define SENSITIVITY 0.002f
#define PI 3.141592f/2.0f

Player::Player() : entity("player")
{
    position = glm::vec4(0.0f, 3.0f, 0.0f, 1.0f);
    facing   = glm::vec4(0.0f, 0.0f, 1.0f,  0.0f);
    viewYaw  = 0.0f;
    viewPitch= 0.0f;
    shootingState = 0;
    speed = 0.10f;
    ammunition = 50;
    isCrouched = false;
    isWalking = false;
    infAmmunition = false;
}

glm::vec4 Player::getPosition()
{
    if(isCrouched){
        isCrouched = false;
        return position - glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    }
    else{
        return position;
    }
}

float Player::getSpeed()
{
    if (isWalking){
        isWalking = false;
        return speed - 0.05f;
    }
    else{
        return speed;
    }
    
}

int Player::getAmmunition()
{
    if (infAmmunition){
        return 9999;
    }
    else{
        return ammunition;
    }
}

void Player::setInfAmmunition()
{
    infAmmunition = true;
}

void Player::walk()
{
    isWalking = true;
}

void Player::crouch()
{
    isCrouched = true;
    isWalking = true;
}

void Player::shoot()
{
    if (getAmmunition() > 0){    
        ammunition--;
        Shot shot = Shot(this->getFacing());
    }
}

void Player::moveView(float dx, float dy)
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
