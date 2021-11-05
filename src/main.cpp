#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>  

#include "Renderer.h"
#include "InputManager.h"
#include "Actor.h"
#include "Command.h"
#include "MoveCommand.h"
#include "CrouchCommand.h"
#include "ExitCommand.h"
#include "Window.h"
#include "Game.h"

int main()
{
    Actor player;
    Game game;

    std::vector<std::tuple<int, Command*>> commandLst = {
        std::make_tuple(GLFW_KEY_W,     new MoveCommand(player, MoveCommand::FORWARD)),
        std::make_tuple(GLFW_KEY_S,     new MoveCommand(player, MoveCommand::BACKWARD)),
        std::make_tuple(GLFW_KEY_A,     new MoveCommand(player, MoveCommand::LEFT)),
        std::make_tuple(GLFW_KEY_D,     new MoveCommand(player, MoveCommand::RIGHT)),
        std::make_tuple(GLFW_KEY_LEFT_CONTROL,     new CrouchCommand(player)),
        std::make_tuple(GLFW_KEY_ESCAPE,new ExitCommand (game))
    };

    InputManager input(commandLst, player);
    Window window(&input);
    Renderer renderer(window.width, window.height);

    while (!window.shouldClose() && game.isRunning())
    {
        input.handleInput();
        renderer.draw(player);
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
