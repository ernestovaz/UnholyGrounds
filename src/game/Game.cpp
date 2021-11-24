#include "Game.h"


Game::Game(Player& player) : scene(player)
{
    running = true;
}

void Game::terminate()
{
    running = false;
}

bool Game::isRunning()
{
    return running;
}
