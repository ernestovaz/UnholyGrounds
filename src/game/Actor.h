#pragma once 

#include <glm/vec4.hpp>

class Actor
{
private:
    glm::vec4 position;
    glm::vec4 facing;
    float speed;
    float viewYaw;
    float viewPitch;
    bool isCrouched;
    bool isWalking;
public:
    Actor();
    glm::vec4 getPosition();
    glm::vec4 getFacing();
    float getSpeed();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveWalk();
    void crouch();
    void moveView(float dx, float dy);
};
