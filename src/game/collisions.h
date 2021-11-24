#pragma once

#include <glm/vec4.hpp>
#include "BoundingBox.h"

bool pointBoundingBoxCollision(glm::vec4 point,BoundingBox box);

bool lineBoundingBoxCollision();

bool pointLineSegment(glm::vec4 point, glm::vec4 p1, glm::vec4 p2);

bool pointSquare(glm::vec4 point, std::vector<glm::vec4> squareVertices);