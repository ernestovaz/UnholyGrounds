
#include "ShootCommand.h"
#include "Actor.h"

ShootCommand::ShootCommand(Actor& a) : player(a)
{
}

void ShootCommand::execute()
{
    player.shoot();
}
