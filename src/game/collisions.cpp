#include "collisions.h"
#include <iostream>

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

bool lineBoundingBoxCollision(glm::vec4 point, glm::vec4 vector, BoundingBox box){
    //Arguments are shot position (point), shot direction (vector) and a bounding box
    bool hit = false;
    std::vector<float> minCoords = box.getMinCoords();
    std::vector<float> maxCoords = box.getMaxCoords();
    bool isInsideX = point.x + vector.x <= maxCoords[0] && point.x + vector.x >= minCoords[0];
    bool isInsideY = point.y + vector.y <= maxCoords[1] && point.y + vector.y >= minCoords[1];
    bool isInsideZ = point.z + vector.z <= maxCoords[2] && point.z + vector.z >= minCoords[2];
    if(isInsideX && isInsideY && isInsideZ)
    {
        hit = true;
    } 

    return hit;
}

bool pointLineSegment(glm::vec4 point, glm::vec4 p1, glm::vec4 p2)
{
    //Arguments are the point and two other points that compose a line segment
    bool xInside = int(point.x) >= int(std::min(p1[0], p2[0])) && int(point.x) <= int(std::max(p1[0], p2[0]));
    bool zInside = int(point.z) >= int(std::min(p1[2], p2[2])) && int(point.z) <= int(std::max(p1[2], p2[2]));
    bool isInside = xInside && zInside;
    return isInside;
}

bool pointSquare(glm::vec4 point, std::vector<glm::vec4> squareVertices)
{
    //Arguments are a vec4 (point) and a vector of points (containing 4 points).
    bool isInsideFirstLine = pointLineSegment(point, squareVertices[0], squareVertices[1]);
    bool isInsideSecondLine = pointLineSegment(point, squareVertices[0], squareVertices[2]);
    bool isInsideThirdLine = pointLineSegment(point, squareVertices[3], squareVertices[1]);
    bool isInsideFourthLine = pointLineSegment(point, squareVertices[3], squareVertices[2]);
    return isInsideFirstLine || isInsideSecondLine || isInsideThirdLine || isInsideFourthLine;
}