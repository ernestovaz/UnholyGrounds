#include "WalkCommand.h"

WalkCommand::WalkCommand(Game& g) : game(g)
{
}

void WalkCommand::execute()
{
    game.playerWalk();
}
