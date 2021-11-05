#pragma once 

#include "Command.h"
#include "Player.h"

class CrouchCommand : public Command
{
public:
    CrouchCommand(Player& actor);
    virtual void execute() override;
private:
    Player& player;
};
