#include <map>
#include <iterator>

#include "Player.h"
#include "InputManager.h" 
#include <GLFW/glfw3.h>

#include <iostream>

InputManager::InputManager(std::vector<std::tuple<int,Command*>> cList, Player& player)
    : player(player)
{
    for(unsigned int i=0; i<cList.size(); i++) {
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
    else{
    }

    std::map<int, bool>::iterator it = heldKeys.find(key); 
    if (it != heldKeys.end())
        it->second = keyState; 
}

void InputManager::mouseButtonCallback(int button, int action, int mods)
{
    bool keyState;
    if(action == GLFW_PRESS){
        keyState = true;
    }
    else if(action == GLFW_RELEASE)
        keyState = false;
    else{
    }

    std::map<int, bool>::iterator it = heldKeys.find(button); 
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

void InputManager::setInitialCursorPos(double xpos, double ypos)
{
    lastCursorPosX = xpos;
    lastCursorPosY = ypos;
}

void InputManager::handleInput()
{
    for(auto& k : heldKeys)
    {
        if(k.second == true){               //if key is held
            Command* targetCommand = commands[k.first];
            targetCommand->execute();       //execute key's command
            if(!targetCommand->isRepeatable())
                k.second = false;
        }
    }
}


