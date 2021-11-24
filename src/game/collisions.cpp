#include "collisions.h"

bool pointBoundingBoxCollision(glm::vec4 point,BoundingBox box){
    std::vector<float> minCoords = box.getMinCoords();
    std::vector<float> maxCoords = box.getMaxCoords();
    bool isInside = false;
    bool isInsideX = point.x <= maxCoords[0] && point.x >= minCoords[0];
    bool isInsideY = point.y <= maxCoords[1] && point.y >= minCoords[1];
    bool isInsideZ = point.z <= maxCoords[2] && point.z >= minCoords[2];
    if(isInsideX && isInsideY && isInsideZ)
    {
        isInside = true;
    }  

    return isInside;
} 

bool lineSphereCollision(){
    //Arguments are a vec4 (vector) and a bounding box?
    return false;
}

bool betweenBoundingBoxes(){
    //Arguments are two bounding boxes.
    return false;
}