#pragma once

#include <glm/vec4.hpp>
#include "BoundingBox.h"

bool pointBoundingBoxCollision(glm::vec4 point,BoundingBox box);

bool lineSphereCollision();

bool betweenBoundingBoxes();