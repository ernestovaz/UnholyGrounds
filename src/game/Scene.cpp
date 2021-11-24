#include "Scene.h"
#include "Matrices.h"
#include "Model.h"

#include <cstdlib>
#include <cmath>

#include <vector>

#define PI 3.14159265f

#define RADIUS 10
#define HEIGHT 20

Scene::Scene(Player& player) : player(player), ground("ground"), sky("sky", Matrix_Scale(20.0f, 20.0f, 20.0f))
{
    this->ambientItem.push_back(Entity(Model("car", false), Matrix_Translate(6.0f,0.0f, 1.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f)));
}

void Scene::spawnSkeleton()
{
    float theta = fmod(rand(),(2.0 * PI)); 
    float x = RADIUS * cos(theta);
    float z = RADIUS * sin(theta);

    Entity skeleton = Entity("skeleton", Matrix_Translate(x, HEIGHT, z));
    this->enemies.push_back(skeleton);
}

