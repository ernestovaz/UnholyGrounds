#include "MoveCommand.h"
#include "Actor.h"

MoveCommand::MoveCommand(Actor& a, Direction d) : actor(a), dir(d)
{
}

void MoveCommand::execute()
{
    switch(dir)
    {
        case(FORWARD):
            actor.moveForward();
            break;
        case(BACKWARD):
            actor.moveBackward();
            break;
        case(LEFT):
            actor.moveLeft();
            break;
        case(RIGHT):
            actor.moveRight();
            break;
    }
}
