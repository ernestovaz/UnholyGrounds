#include "MoveCommand.h"
#include "Game.h"

MoveCommand::MoveCommand(Game& g, Direction d) : game(g), dir(d)
{
}

void MoveCommand::execute()
{
    switch(dir)
    {
        case(FORWARD):
            game.scene.player.moveForward();
            break;
        case(BACKWARD):
            game.scene.player.moveBackward();
            break;
        case(LEFT):
            game.scene.player.moveLeft();
            break;
        case(RIGHT):
            game.scene.player.moveRight();
            break;
    }
}
