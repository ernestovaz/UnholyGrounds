#include "Game.h"

Game::Game()
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
