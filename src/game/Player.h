#pragma once

#include "Actor.h"
#include "Entity.h"
#include "Shot.h"

class Player : public Actor
{
private:
    float viewYaw;
    float viewPitch;
    int ammunition;
    bool infAmmunition;
public:
    Entity entity;
    float shootingState;
    bool isWalking;  
    bool isShooting;
    bool isCrouched;
    Player();
    virtual glm::vec4 getPosition() override;
    virtual float getSpeed() override;
    int getAmmunition();
    void setInfAmmunition();
    void shoot();
    void moveView(float dx, float dy);
};

