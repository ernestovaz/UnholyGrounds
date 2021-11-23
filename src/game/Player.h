#pragma once

#include "Actor.h"
#include "Entity.h"

class Player : public Actor
{
private:
    float viewYaw;
    float viewPitch;
    int ammunition;
    int shootingState;  
    bool isShooting;
    bool isCrouched;
    bool isWalking;
    bool infAmmunition;
public:
    Entity entity;
    Player();
    virtual glm::vec4 getPosition() override;
    virtual float getSpeed() override;
    int getAmmunition();
    void setInfAmmunition();
    void walk();
    void crouch();
    void shoot();
    void moveView(float dx, float dy);
};

