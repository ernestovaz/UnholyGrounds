#pragma once

class Game
{

private:
    bool running;

public:
    Game();
    void terminate();
    bool isRunning();
};
