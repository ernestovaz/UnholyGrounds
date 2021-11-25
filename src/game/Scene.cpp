#include "Scene.h"
#include "Matrices.h"
#include "Model.h"

#include <cstdlib>
#include <cmath>

#include <vector>

#include <iostream>

#define PI 3.14159265f

#define RADIUS 10

Scene::Scene(Player& player) 
    : player(player), ground("ground", false),sky("sky", false, Matrix_Scale(20.0f, 20.0f, 20.0f)),
    border("border", false, Matrix_Scale(20.0f, 20.0f, 20.0f))
{
    this->ambientItem.push_back(Entity(Model("car", true, false), Matrix_Translate(30.0f,0.0f, 1.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f)));
}

void Scene::spawnSkeleton()
{
    std::vector<glm::vec4> points;
    points.push_back(glm::vec4(-0.381485,0.000632 ,0.569600 ,1.0f));
    points.push_back(glm::vec4(-0.381485,4.000632 ,0.569600 ,1.0f));
    points.push_back(glm::vec4(-0.381485,0.000632 ,-0.570705,1.0f));
    points.push_back(glm::vec4(-0.381485,4.000632 ,-0.570705,1.0f));
    points.push_back(glm::vec4(0.319983, 0.000000 ,0.563823 ,1.0f));
    points.push_back(glm::vec4(0.319983, 4.000000 ,0.563823 ,1.0f));
    points.push_back(glm::vec4(0.319983, 0.000000 ,-0.576482,1.0f));
    points.push_back(glm::vec4(0.319983, 4.000000 ,-0.576482,1.0f));

    BoundingBox box = BoundingBox(points);

    float theta = fmod(rand(),(2.0 * PI)); 
    float x = RADIUS * cos(theta);
    float z = RADIUS * sin(theta);

    Entity skeleton = Entity("skeleton", box, Matrix_Rotate_Y(theta) * Matrix_Translate(x, 0.0, z));
    this->enemies.push_back(skeleton);
}

