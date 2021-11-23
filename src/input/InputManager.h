#pragma once

#include <map>
#include <tuple>
#include <vector>

#include "Command.h" 
#include "Player.h" 

#include <GLFW/glfw3.h>

class InputManager
{

public:

    InputManager(std::vector <std::tuple<int,Command*>> cList, Player& player);
    void keyCallback(int key, int action, int mods);
    void cursorCallback(double xpos, double ypos);
    void setInitialCursorPos(double xpos, double ypos);
    void handleInput();

private:
    std::map<int,bool>    heldKeys;
    std::map<int,Command*> commands;
    float lastCursorPosX;
    float lastCursorPosY;
    Player& player;
};

