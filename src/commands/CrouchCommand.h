#pragma once 

#include "Command.h"
#include "../game/Game.h"

class CrouchCommand : public Command
{
public:
    CrouchCommand(Game& game);
    virtual void execute() override;
private:
    Game& game;
};
