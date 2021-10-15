#pragma once

#include <map>
#include <tuple>
#include <GLFW/glfw3.h>

#include "Command.h" 

class InputManager
{

public:

    InputManager(std::tuple<int,Command*> cList[], int count);
    void callback(int key, int action, int mods);
    void handleInput(Actor&);

private:
    std::map<int,bool>    heldKeys;
    std::map<int,Command*> commands;
};

