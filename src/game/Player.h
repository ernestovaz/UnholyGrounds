#pragma once

#include "Actor.h"

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

