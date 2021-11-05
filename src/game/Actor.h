#pragma once 

#include <glm/vec4.hpp>

class Actor
{
protected:
    glm::vec4 position;
    glm::vec4 facing;
    float speed;
    int health;

public:
    Actor();
    virtual glm::vec4 getPosition();
    glm::vec4 getFacing();
    virtual float getSpeed();
    int getHealth();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

};
