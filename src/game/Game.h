#pragma once

#include "Scene.h"
#include "Player.h"

class Game
{

private:
    bool running;

public:
    Scene scene;

    Game(Player& player);
    void terminate();
    bool isRunning();
};
