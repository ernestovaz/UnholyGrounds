#include <vector>

#include "Entity.h"

#pragma once

class Scene
{
public:
    Scene();
    Entity ground;
    Entity sky;
    std::vector<Entity> enemies;
    std::vector<Entity> ambientItem;
};
