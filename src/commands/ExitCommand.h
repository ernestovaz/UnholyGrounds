#pragma once

#include "Command.h"
#include "Game.h"

class ExitCommand : public Command
{
    public:
        ExitCommand(Game& game);
        virtual void execute() override; 
    private: 
        Game& game; 
};

