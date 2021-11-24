#include "Scene.h"
#include "Matrices.h"
#include "Model.h"

#include <vector>

Scene::Scene() : ground("ground"), sky("sky", Matrix_Scale(20.0f, 20.0f, 20.0f))
{
    this->ambientItem.push_back(Entity(Model("car", false), Matrix_Translate(6.0f,0.0f, 1.0f) * Matrix_Scale(0.02f, 0.02f, 0.02f)));
}

