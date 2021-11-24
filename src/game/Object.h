#pragma once

#include <glm/vec4.hpp>
#include <vector>

class Object{
    public:
        std::vector<glm::vec4> boundingBox;
        Object();
        std::vector<float> getMinCoords();
        std::vector<float> getMaxCoords();
};