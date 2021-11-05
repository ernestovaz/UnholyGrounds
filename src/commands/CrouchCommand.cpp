
#include "CrouchCommand.h"
#include "Actor.h"

CrouchCommand::CrouchCommand(Player& a) : player(a)
{
}

void CrouchCommand::execute()
{
    player.crouch();
}
