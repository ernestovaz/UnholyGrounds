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
        checkCollisions();
    }
}

void Game::checkCollisions()
{
    for (Entity item : scene.ambientItem)
    {
        bool playerInside = pointBoundingBoxCollision(scene.player.getPosition(), item.model.getBoundingBox());
    }
    for (Entity enemy : scene.enemies)
    {
        bool playerinside = pointBoundingBoxCollision(scene.player.getPosition(), enemy.model.getBoundingBox());
    }

}

void Game::movePlayerForward()
{
    scene.player.moveForward();
}

void Game::movePlayerBackward()
{
    scene.player.moveBackward();
}

void Game::movePlayerLeft()
{
    scene.player.moveLeft();
}

void Game::movePlayerRight()
{
    scene.player.moveRight();
}