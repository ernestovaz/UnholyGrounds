#include <map>
#include <iterator>
#include <iostream>

#include <GLFW/glfw3.h>

#include "InputManager.h" 

InputManager::InputManager(std::tuple<int,Command*> cList[], int count)
{
    for(int i=0; i<count; i++) {
        int key          = std::get<0>(cList[i]);
        Command* command = std::get<1>(cList[i]);
        heldKeys[key] = false;
        commands[key] = command;
    }
}

void InputManager::callback(int key, int action, int mods)
{
    bool state;
    if(action == GLFW_PRESS){
        state = true;
    }
    else if(action == GLFW_RELEASE)
        state = false;
    else
        return;

    std::map<int, bool>::iterator it = heldKeys.find(key); 
    if (it != heldKeys.end())
        it->second = state; 
}

void InputManager::handleInput(Actor& actor)
{
    for(auto const& k : heldKeys)
    {
        if(k.second == true){                            //if key is held
            commands[k.first]->execute(actor);       //execute key's command
        }
    }
}


