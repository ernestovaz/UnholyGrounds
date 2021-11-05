
#include "CrouchCommand.h"
#include "Actor.h"

CrouchCommand::CrouchCommand(Actor& a) : player(a)
{
}

void CrouchCommand::execute()
{
    player.crouch();
}
