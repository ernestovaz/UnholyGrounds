
#include "WalkCommand.h"
#include "Actor.h"

WalkCommand::WalkCommand(Actor& a) : player(a)
{
}

void WalkCommand::execute()
{
    player.walk();
}
