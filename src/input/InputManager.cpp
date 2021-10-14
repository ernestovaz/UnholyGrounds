#include <GLFW/glfw3.h>

#include "InputManager.h" 

InputManager::InputManager()
{
    heldKeys = new bool[keycount];
    commands = new Command*[keycount];
}

InputManager::~InputManager()
{
    delete [] heldKeys;
    delete [] commands;
}

void InputManager::insertCommand(Command* command, Key key)
{
    commands[key] = command;
}

void InputManager::handleInput(int key, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_W:
                commands[KeyW]->execute();
                break;
            case GLFW_KEY_A:
                commands[KeyA]->execute();
                break;
            case GLFW_KEY_S:
                commands[KeyS]->execute();
                break;
            case GLFW_KEY_D:
                commands[KeyD]->execute();
                break;
        }
    }
}


