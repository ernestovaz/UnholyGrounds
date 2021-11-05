
#include "WalkCommand.h"
#include "Player.h"

WalkCommand::WalkCommand(Player& a) : player(a)
{
}

void WalkCommand::execute()
{
    player.walk();
}
