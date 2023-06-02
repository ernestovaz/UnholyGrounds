#include "Game.h"
#include "Collisions.h"
#include "Enemy.h"
#include "Shot.h"

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <iostream>  

#define SPAWNTIME 10

Game::Game(Player& player) : scene(player)
{
    running = true;
    spawnClock = glfwGetTime();
    limits.push_back(glm::vec4(-45.0f,0.0f,-45.0f,1.0f));
    limits.push_back(glm::vec4(45.0f,0.0f,-45.0f,1.0f));
    limits.push_back(glm::vec4(-45.0f,0.0f,45.0f,1.0f));
    limits.push_back(glm::vec4(45.0f,0.0f,45.0f,1.0f));
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
    if(glfwGetTime() - spawnClock >= SPAWNTIME){
        scene.spawnSkeleton();
        spawnClock = glfwGetTime();
    }
}

bool Game::isOffLimits(glm::vec4 position)
{ //checks if given position is off limits
    return pointSquare(position, limits);
}

bool Game::checkCollisions(glm::vec4 position)
{ //checks collisions between given position and all enemies and ambient itens in the scene.
    for (Entity item : scene.ambientItem)
    {
        if(pointBoundingBoxCollision(position, item.getGlobalBoundingBox()))
        {
            return true;
        }
    }
    for (Enemy enemy : scene.enemies)
    {
        if(pointBoundingBoxCollision(position, enemy.entity.getGlobalBoundingBox()))
        {
            return true;
        }
    }
    return false;
}

bool Game::shotHit(Shot shot)
{
    for (int i=0; i < scene.enemies.size(); i++)
    {
        if (raySphereCollision(shot.position, shot.direction, Enemy::HEAD_SPHERE_ORIGIN*scene.enemies[i].entity.matrix, Enemy::HEAD_SPHERE_RADIUS))
        {
            scene.enemies.erase(scene.enemies.begin() + i);
            return true;
        }
        /*
        if (lineBoundingBoxCollision(shot.position, shot.direction, scene.enemies[i].getGlobalBoundingBox()))
        {
            scene.enemies.erase(scene.enemies.begin() + i);
            return true;
        }
        */
    }
    return false;
}

void Game::movePlayerForward()
{
    glm::vec3 forward(scene.player.getFacing());
    forward.y = 0;
    glm::vec4 hmForward(glm::normalize(forward), 0.0f);
    float playerSpeed = scene.player.speed;
    if (scene.player.isWalking){
        playerSpeed = 0.5*playerSpeed;
    }
    glm::vec4 newPosition = scene.player.getPosition() + hmForward * playerSpeed;

    bool causeCollision = checkCollisions(newPosition);
    bool offLimits = isOffLimits(newPosition);
    if (!causeCollision && !offLimits){
        scene.player.moveForward();
    }
}

void Game::movePlayerBackward()
{
    glm::vec3 backward(-scene.player.getFacing());
    backward.y = 0;
    glm::vec4 hmBackward(glm::normalize(backward), 0.0f);
    float playerSpeed = scene.player.speed;
    if (scene.player.isWalking){
        playerSpeed = 0.5*playerSpeed;
    }
    glm::vec4 newPosition = scene.player.getPosition() + hmBackward * playerSpeed;

    bool causeCollision = checkCollisions(newPosition);
    bool offLimits = isOffLimits(newPosition);
    if (!causeCollision && !offLimits){
        scene.player.moveBackward();
    }
}

void Game::movePlayerLeft()
{
    glm::vec3 forward(scene.player.getFacing());
    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    glm::vec4 hmLeft(left, 0.0f);
    float playerSpeed = scene.player.speed;
    if (scene.player.isWalking){
        playerSpeed = 0.5*playerSpeed;
    }
    glm::vec4 newPosition = scene.player.getPosition() + hmLeft * playerSpeed;

    bool causeCollision = checkCollisions(newPosition);
    bool offLimits = isOffLimits(newPosition);
    if (!causeCollision && !offLimits){
        scene.player.moveLeft();
    }
}

void Game::movePlayerRight()
{
    glm::vec3 backward(-scene.player.getFacing());
    glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward);
    glm::vec4 hmRight(right, 0.0f);
    float playerSpeed = scene.player.speed;
    if (scene.player.isWalking){
        playerSpeed = 0.5*playerSpeed;
    }
    glm::vec4 newPosition = scene.player.getPosition() + hmRight * playerSpeed;

    bool causeCollision = checkCollisions(newPosition);
    bool offLimits = isOffLimits(newPosition);
    if (!causeCollision && !offLimits){
        scene.player.moveRight();
    }
}

void Game::playerShoot()
{
    scene.player.shoot();
    Shot shot = Shot(scene.player.getFacing(), scene.player.getPosition());
    bool hit = shotHit(shot);
}

void Game::playerCrouch()
{
    scene.player.isCrouched = true;
    scene.player.isWalking = true;
}

void Game::playerWalk()
{
    scene.player.isWalking = true;
}
