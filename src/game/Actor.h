#include <glm/vec4.hpp>

class Actor
{
private:
    glm::vec4 position;
    glm::vec4 facing;
public:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
};
