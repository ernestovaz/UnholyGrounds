
#include "WalkCommand.h"
#include "Game.h"

WalkCommand::WalkCommand(Game& g) : game(g)
{
}

void WalkCommand::execute()
{
    game.playerWalk();
}
