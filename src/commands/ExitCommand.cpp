#include "ExitCommand.h"

ExitCommand::ExitCommand(Game& game) : game(game)
{
}

void ExitCommand::execute()
{
    this->game.terminate();
}
