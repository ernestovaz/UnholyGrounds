
#include "ShootCommand.h"
#include "Player.h"

ShootCommand::ShootCommand(Player& a) : player(a)
{
}

void ShootCommand::execute()
{
    player.shoot();
}
