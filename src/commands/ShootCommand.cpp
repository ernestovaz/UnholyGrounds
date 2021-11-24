
#include "ShootCommand.h"
#include "Player.h"
#include <iostream>

ShootCommand::ShootCommand(Player& a) : player(a)
{
    this->repeatable = false;
}

void ShootCommand::execute()
{
    if(!player.isShooting)
        player.shoot();
}
