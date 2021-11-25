#pragma once

#include <glm/vec4.hpp>

class Shot
{
public:
    Shot(glm::vec4 dir, glm::vec4 pos);
    glm::vec4 direction;
    glm::vec4 position;
};