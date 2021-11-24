#include "Scene.h"
#include "Matrices.h"
#include "Model.h"

#include <cstdlib>
#include <cmath>

#include <vector>

#include <iostream>

#define PI 3.14159265f

#define RADIUS 5
#define HEIGHT 0

Scene::Scene(Player& player) 
    : player(player), ground("ground", false),sky("sky", false, Matrix_Scale(20.0f, 20.0f, 20.0f)),
    border("border", false, Matrix_Scale(20.0f, 20.0f, 20.0f))
{
    this->ambientItem.push_back(Entity(Model("car", true, false), Matrix_Translate(6.0f,0.0f, 1.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f)));
}

void Scene::spawnSkeleton()
{
    float theta = fmod(rand(),(2.0 * PI)); 
    float x = RADIUS * cos(theta);
    float z = RADIUS * sin(theta);

    Entity skeleton = Entity("skeleton", true, Matrix_Translate(x, HEIGHT, z) * Matrix_Scale(2.0f, 2.0f, 2.0f));
    this->enemies.push_back(skeleton);
}

