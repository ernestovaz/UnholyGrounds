#pragma once

#include "Command.h"
#include "Window.h"

class ExitCommand : public Command
{

    public:
        ExitCommand(Window& w);
        virtual void execute() override;
    
    private: 
        Window& window;
};
