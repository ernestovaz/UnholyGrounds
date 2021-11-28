#pragma once

#include "Scene.h"
#include "Player.h"
#include "Shot.h"

class Game
{

private:
    bool running;
    float startClock;
    float spawnClock;

public:
    Scene scene;

    Game(Player& player);
    void terminate();
    bool isRunning();
    void update();
    bool isOffLimits(glm::vec4 position);
    bool checkCollisions(glm::vec4 position);
    bool shotHit(Shot shot);
    void movePlayerForward();
    void movePlayerBackward();
    void movePlayerRight();
    void movePlayerLeft();
    void playerShoot();
    void playerCrouch();
    void playerWalk();
    std::vector<glm::vec4> limits;
};
