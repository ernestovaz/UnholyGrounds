#include "Game.h"
#include "collisions.h"

#include <GLFW/glfw3.h>
#include <iostream>  

Game::Game(Player& player) : scene(player)
{
    running = true;
    startClock = glfwGetTime();
    spawnClock = glfwGetTime();
    limits.push_back(glm::vec4(-50.0f,-50.0f,0.0f,1.0f));
    limits.push_back(glm::vec4(50.0f,-50.0f,0.0f,1.0f));
    limits.push_back(glm::vec4(-50.0f,50.0f,0.0f,1.0f));
    limits.push_back(glm::vec4(50.0f,50.0f,0.0f,1.0f));
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

bool Game::checkCollisions(glm::vec4 position)
{ //check collisions between given position and all enemies and ambient itens in the scene.
    for (Entity item : scene.ambientItem)
    {
        if(pointBoundingBoxCollision(position, item.getGlobalBoundingBox()))
        {
            return true;
        }
    }
    for (Entity enemy : scene.enemies)
    {
        if(pointBoundingBoxCollision(position, enemy.getGlobalBoundingBox()))
        {
            return true;
        }
    }
    return false;
}

void Game::movePlayerForward()
{
    glm::vec3 forward(scene.player.getFacing());
    forward.y = 0;
    glm::vec4 hmForward(glm::normalize(forward), 0.0f);
    glm::vec4 newPosition = scene.player.getPosition() + hmForward * scene.player.getSpeed();

    bool causeCollision = checkCollisions(newPosition);
    if (!causeCollision){
        scene.player.moveForward();
    }
}

void Game::movePlayerBackward()
{
    glm::vec3 backward(-scene.player.getFacing());
    backward.y = 0;
    glm::vec4 hmBackward(glm::normalize(backward), 0.0f);
    glm::vec4 newPosition = scene.player.getPosition() + hmBackward * scene.player.getSpeed();

    bool causeCollision = checkCollisions(newPosition);
    if (!causeCollision){
        scene.player.moveBackward();
    }
}

void Game::movePlayerLeft()
{
    glm::vec3 forward(scene.player.getFacing());
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 hmLeft(left, 0.0f);
    glm::vec4 newPosition = scene.player.getPosition() + hmLeft * scene.player.getSpeed();

    bool causeCollision = checkCollisions(newPosition);
    if (!causeCollision){
        scene.player.moveLeft();
    }
}

void Game::movePlayerRight()
{
    glm::vec3 backward(-scene.player.getFacing());
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 hmRight(right, 0.0f);
    glm::vec4 newPosition = scene.player.getPosition() + hmRight * scene.player.getSpeed();

    bool causeCollision = checkCollisions(newPosition);
    if (!causeCollision){
        scene.player.moveRight();
    }
}
