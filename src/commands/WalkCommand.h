#pragma once 

#include "Command.h"
#include "Game.h"

class WalkCommand : public Command
{
public:
    WalkCommand(Game& game);
    virtual void execute() override;
private:
    Game& game;
};
