#pragma once

#include "Command.h"

class ExitCommand : public Command
{

    public:
        ExitCommand();
        virtual void execute() override; 

};
