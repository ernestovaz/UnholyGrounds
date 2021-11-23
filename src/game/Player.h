#pragma once

#include "Actor.h"
#include "Entity.h"

class Player : public Actor
{
private:
    int ammunition;
    float viewYaw;
    float viewPitch;
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

