#include <vector>

#include "Entity.h"
#include "Player.h"

#pragma once

class Scene
{
public:
    Player& player;
    Entity ground;
    Entity sky;
    Entity border;
    std::vector<Entity> enemies;
    std::vector<Entity> ambientItem;

    Scene(Player& player);
    void spawnSkeleton();
};
