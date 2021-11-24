#pragma once

#include "Actor.h"
#include "Entity.h"

class Player : public Actor
{
private:
    float viewYaw;
    float viewPitch;
    int ammunition;
    bool isCrouched;
    bool isWalking;
    bool infAmmunition;
public:
    Entity entity;
    float shootingState;  
    bool isShooting;
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

