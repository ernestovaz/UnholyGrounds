#pragma once

#include <glm/vec4.hpp>
#include <vector>
#include "BoundingBox.h"

bool pointBoundingBoxCollision(glm::vec4 point,BoundingBox box);
bool lineBoundingBoxCollision(glm::vec4 position, glm::vec4 vector, BoundingBox box);
bool pointLineSegment(glm::vec4 point, glm::vec4 p1, glm::vec4 p2);
bool pointSquare(glm::vec4 point, std::vector<glm::vec4> squareVertices);
bool raySphere(glm::vec4 rayOrigin, glm::vec4 rayDirection, glm::vec4 sphereOrigin, glm::vec4 sphereRadius, float maxDistance = 0);

std::vector<float> quadraticRoot(float a, float b, float c);
