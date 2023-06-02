#pragma once 

#include "Command.h"
#include "../game/Game.h"

class ShootCommand : public Command
{
public:
    ShootCommand(Game& game);
    virtual void execute() override;
private:
    Game& game;
};
