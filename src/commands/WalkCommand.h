#pragma once 

#include "Command.h"
#include "Actor.h"

class WalkCommand : public Command
{
public:
    WalkCommand(Actor& actor);
    virtual void execute() override;
private:
    Actor& player;
};
