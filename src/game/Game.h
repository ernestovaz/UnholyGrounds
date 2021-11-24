#pragma once

#include "Scene.h"
#include "Player.h"

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
    bool checkCollisions(glm::vec4 position);
    void movePlayerForward();
    void movePlayerBackward();
    void movePlayerRight();
    void movePlayerLeft();
};
