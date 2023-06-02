#include "CrouchCommand.h"
#include <iostream>

CrouchCommand::CrouchCommand(Game& g) : game(g)
{
}

void CrouchCommand::execute()
{
    game.playerCrouch();
}
