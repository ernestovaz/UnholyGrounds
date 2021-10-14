#pragma once

#include "Command.h" 

class InputManager
{

public:

    enum Key
    {
        KeyW,
        KeyA,
        KeyS,
        KeyD,
        keycount //the last int value in enum, since it's the last item
    };

    InputManager();
    ~InputManager();
    void insertCommand(Command* command, Key key);
    void handleInput(int key, int action, int mods);

private:
    bool*       heldKeys;
    Command**    commands;
};

