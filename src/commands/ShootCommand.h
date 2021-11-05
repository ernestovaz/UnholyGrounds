#pragma once 

#include "Command.h"
#include "Player.h"

class ShootCommand : public Command
{
public:
    ShootCommand(Player& actor);
    virtual void execute() override;
private:
    Player& player;
};
