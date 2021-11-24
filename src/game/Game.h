#pragma once

#include "Scene.h"

class Game
{

private:
    bool running;

public:
    Game();
    void terminate();
    bool isRunning();
};
