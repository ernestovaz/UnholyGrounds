#pragma once

#include "Command.h"
#include "Game.h"


class MoveCommand : public Command
{

    public:
        enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};
        MoveCommand(Game& game, Direction dir);
        virtual void execute() override; 

    private:
        Game& game;
        Direction dir;
};


