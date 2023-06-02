#include "Scene.h"
#include "../renderer/Matrices.h"
#include "../renderer/Model.h"

#include <cstdlib>
#include <cmath>

#include <vector>

#include <iostream>

#define PI 3.14159265f

#define RADIUS 20

Scene::Scene(Player& player) 
    : player(player), ground("ground", false),sky("sky", false, Matrix_Scale(20.0f, 20.0f, 20.0f)),
    border("border", false, Matrix_Scale(20.0f, 20.0f, 20.0f))
{
    this->ambientItem.push_back(Entity(Model("car", true, false), Matrix_Translate(30.0f,0.0f, 1.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f)));

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

    this->skeleton = Entity("skeleton", box);
}

void Scene::spawnSkeleton()
{

    float theta = fmod(rand(),(2.0 * PI)); 
    float x = RADIUS * cos(theta);
    float z = RADIUS * sin(theta);
    Entity newSkeletonEntity = this->skeleton;
    newSkeletonEntity.matrix = newSkeletonEntity.matrix*(Matrix_Translate(x, 0.0, z) * Matrix_Rotate_Y(theta));
    glm::vec4 facing = glm::vec4(cos(theta), 0, sin(theta), 0.0);
    glm::vec4 position = glm::vec4(x, 0.0, z, 1.0);
    Enemy newSkeleton = Enemy(newSkeletonEntity, position, facing);

    this->enemies.push_back(newSkeleton);
}
