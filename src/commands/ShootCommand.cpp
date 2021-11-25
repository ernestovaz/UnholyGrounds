
#include "ShootCommand.h"
#include <iostream>

ShootCommand::ShootCommand(Game& g) : game(g)
{
    this->repeatable = false;
}

void ShootCommand::execute()
{
    if(!game.scene.player.isShooting)
        game.playerShoot();
}
