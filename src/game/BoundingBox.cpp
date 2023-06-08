#include <glm/vec4.hpp>

#include "BoundingBox.h"

BoundingBox::BoundingBox(std::vector<glm::vec4> box)
{
    boundingBox = box;
}

BoundingBox::BoundingBox()
{//object's bounding box
    for (int i = 0; i<= 7; i++){
        boundingBox.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }
}

std::vector<float> BoundingBox::getMinCoords() //returns min (x,y,z) beteween bounding box's vertices 
{
    std::vector<float> minCoords = {1000.0, 1000.0, 1000.0};
    for (int c = 0; c <= 2; c++){
        for (int v = 0; v <= 7; v++){
            if(boundingBox[v][c] < minCoords[c]){
                minCoords[c] = boundingBox[v][c];
            }
        }
    }
    return minCoords;
}

std::vector<float> BoundingBox::getMaxCoords() //returns max (x,y,z) between bounding box's vertices
{
    std::vector<float> maxCoords = {-1000.0, -1000.0, -1000.0};
    for (int c = 0; c <= 2; c++){
        for (int v = 0; v <= 7; v++){
            if(boundingBox[v][c] > maxCoords[c]){
                maxCoords[c] = boundingBox[v][c];
            }
        }
    }
    return maxCoords;
}
