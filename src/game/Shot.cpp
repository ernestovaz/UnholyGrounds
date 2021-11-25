#include <glm/glm.hpp>
#include <glm/vec4.hpp>

#include "Shot.h"

Shot::Shot(glm::vec4 dir, glm::vec4 pos)
{
    direction = dir;
    position = pos;
}