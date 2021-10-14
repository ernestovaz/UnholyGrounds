#include <map>
#include <iterator>

#include <GLFW/glfw3.h>

#include "InputManager.h" 

InputManager::InputManager(std::tuple<int, Command*> commandList[])
{
    int count = sizeof(commandList)/sizeof(std::tuple<int, Command*>);
    for(int i=0; i<count; i++) {
        int key          = std::get<0>(commandList[i]);
        Command* command = std::get<1>(commandList[i]);
        heldKeys[key] = false;
        commands[key] = command;
    }
}

void InputManager::callback(int key, int action, int mods)
{
    bool state;
    if(action == GLFW_PRESS)
        state = true;
    else if(action == GLFW_RELEASE)
        state = false;
    else
        return;

    std::map<int, bool>::iterator it = heldKeys.find(key); 
    if (it != heldKeys.end())
        it->second = state; 
}

void InputManager::handleInput()
{
    for(auto const& k : heldKeys)
    {
        if(k.second)                            //if key is held
            commands[k.first]->execute();       //execute key's command
    }
}


