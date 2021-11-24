#pragma once

#include <glm/vec4.hpp>
#include "BoundingBox.h"

bool PointBoundingBoxCollision(glm::vec4 point,BoundingBox box);

bool LineSphereCollision();

bool BetweenBoundingBoxes();