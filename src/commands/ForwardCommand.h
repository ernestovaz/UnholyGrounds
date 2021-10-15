#pragma once

#include "Command.h"
#include "Actor.h"

class ForwardCommand : public Command
{
public:
    virtual void execute(Actor& actor) override { actor.moveForward(); }
};


