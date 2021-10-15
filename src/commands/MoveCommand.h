#pragma once

#include "Command.h"
#include "Actor.h"


class MoveCommand : public Command
{

public:
    enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};
    MoveCommand(Actor& actor, Direction dir);
    virtual void execute() override; 

private:
    Actor& actor;
    Direction dir;
};


