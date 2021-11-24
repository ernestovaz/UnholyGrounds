#pragma once

#include <glm/vec4.hpp>
#include <vector>

class BoundingBox{
    public:
        std::vector<glm::vec4> boundingBox;
        BoundingBox();
        std::vector<float> getMinCoords();
        std::vector<float> getMaxCoords();
};