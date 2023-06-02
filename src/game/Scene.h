#include <vector>

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

#pragma once

class Scene
{
public:
    Player& player;
    Entity ground;
    Entity sky;
    Entity border;
    Entity skeleton;
    std::vector<Enemy> enemies;
    std::vector<Entity> ambientItem;

    Scene(Player& player);
    void spawnSkeleton();
    void spawnSkeletonInCenter();
};
