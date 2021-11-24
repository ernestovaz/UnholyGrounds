#include "Game.h"
#include "collisions.h"

#include <GLFW/glfw3.h>  

Game::Game(Player& player) : scene(player)
{
    running = true;
    startClock = glfwGetTime();
    spawnClock = glfwGetTime();
}

void Game::terminate()
{
    running = false;
}

bool Game::isRunning()
{
    return running;
}

void Game::update()
{
    if(glfwGetTime() - spawnClock >= 10){
        scene.spawnSkeleton();
        spawnClock = glfwGetTime();
    }
}

void Game::checkCollisions()
{
    

}