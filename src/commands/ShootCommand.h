#pragma once 

#include "Command.h"
#include "Actor.h"

class ShootCommand : public Command
{
public:
    ShootCommand(Actor& actor);
    virtual void execute() override;
private:
    Actor& player;
};
