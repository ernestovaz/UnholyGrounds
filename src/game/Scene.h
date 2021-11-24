#include <vector>

#include "Entity.h"

#pragma once

class Scene
{
public:
    Scene();
private:    
    Entity ground;
    Entity sky;
    //std::vector<Entity> enemies;
    //std::vector<Entity> ambientItem;
};
