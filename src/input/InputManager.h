#pragma once

#include <map>
#include <tuple>

#include "Command.h" 

class InputManager
{

public:

    InputManager(std::tuple<int, Command*> commandList[]);
    void callback(int key, int action, int mods);
    void handleInput();

private:
    std::map<int,bool>    heldKeys;
    std::map<int,Command*> commands;
};

