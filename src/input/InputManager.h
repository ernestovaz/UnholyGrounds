#pragma once

#include <map>
#include <tuple>
#include <GLFW/glfw3.h>

#include "Command.h" 

class InputManager
{

public:

    InputManager(std::tuple<int,Command*> cList[], int count, Actor& player);
    void keyCallback(int key, int action, int mods);
    void cursorCallback(double xpos, double ypos);
    void setInitialCursorPos(double xpos, double ypos);
    void handleInput();

private:
    std::map<int,bool>    heldKeys;
    std::map<int,Command*> commands;
    float lastCursorPosX;
    float lastCursorPosY;
    Actor& player;
};

