#pragma once

#include "Actor.h"

class Command
{

public:
    virtual void execute(Actor& actor) = 0;

};
