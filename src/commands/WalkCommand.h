#pragma once 

#include "Command.h"
#include "Player.h"

class WalkCommand : public Command
{
public:
    WalkCommand(Player& actor);
    virtual void execute() override;
private:
    Player& player;
};
