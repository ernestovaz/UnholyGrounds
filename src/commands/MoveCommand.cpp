#include "MoveCommand.h"

MoveCommand::MoveCommand(Game& g, Direction d) : game(g), dir(d)
{
}

void MoveCommand::execute()
{
    switch(dir)
    {
        case(FORWARD):
            game.movePlayerForward();
            break;
        case(BACKWARD):
            game.movePlayerBackward();
            break;
        case(LEFT):
            game.movePlayerLeft();
            break;
        case(RIGHT):
            game.movePlayerRight();
            break;
    }
}
