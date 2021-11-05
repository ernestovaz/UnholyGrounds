#pragma once 

#include <glm/vec4.hpp>

class Actor
{
private:
    glm::vec4 position;
    glm::vec4 facing;
    float speed;
    int health;
    int ammunition;
    float viewYaw;
    float viewPitch;
    bool isCrouched;
    bool isWalking;
    bool infAmmunition;
public:
    Actor();
    glm::vec4 getPosition();
    glm::vec4 getFacing();
    float getSpeed();
    int getHealth();
    int getAmmunition();
    void setInfAmmunition();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveWalk();
    void crouch();
    void shoot();
    void moveView(float dx, float dy);
};
