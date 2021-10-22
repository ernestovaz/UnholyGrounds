#include <map>
#include <iterator>

#include <GLFW/glfw3.h>

#include "InputManager.h" 

InputManager::InputManager(std::tuple<int,Command*> cList[], int count, Actor& player)
    : player(player)
{
    for(int i=0; i<count; i++) {
        int key          = std::get<0>(cList[i]);
        Command* command = std::get<1>(cList[i]);
        heldKeys[key] = false;
        commands[key] = command;
    }
}

void InputManager::keyCallback(int key, int action, int mods)
{
    bool keyState;
    if(action == GLFW_PRESS){
        keyState = true;
    }
    else if(action == GLFW_RELEASE)
        keyState = false;
    else
        return;

    std::map<int, bool>::iterator it = heldKeys.find(key); 
    if (it != heldKeys.end())
        it->second = keyState; 
}

void InputManager::cursorCallback(double xpos, double ypos)
{
    float dx = xpos - lastCursorPosX;
    float dy = ypos - lastCursorPosY;
    player.moveView(dx, dy);
    lastCursorPosX = xpos;
    lastCursorPosY = ypos;
}

void InputManager::handleInput()
{
    for(auto const& k : heldKeys)
    {
        if(k.second == true){                            //if key is held
            commands[k.first]->execute();       //execute key's command
        }
    }
}


