#pragma once 

#include "Command.h"
#include "Actor.h"

class CrouchCommand : public Command
{
public:
    CrouchCommand(Actor& actor);
    virtual void execute() override;
private:
    Actor& player;
};
