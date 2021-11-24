
#include "CrouchCommand.h"
#include "Actor.h"
#include <iostream>

CrouchCommand::CrouchCommand(Player& a) : player(a)
{
}

void CrouchCommand::execute()
{
    player.crouch();
}
