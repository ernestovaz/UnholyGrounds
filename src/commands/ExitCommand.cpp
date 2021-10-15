#include "ExitCommand.h"
#include "Window.h"

ExitCommand::ExitCommand(Window& w): window(w)
{
}

void ExitCommand::execute()
{
    window.closeWindow();
}
