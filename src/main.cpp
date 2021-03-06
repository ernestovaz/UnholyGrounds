#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>  

#include "Renderer.h"
#include "InputManager.h"
#include "Actor.h"
#include "Player.h"
#include "Command.h"
#include "MoveCommand.h"
#include "CrouchCommand.h"
#include "ShootCommand.h"
#include "WalkCommand.h"
#include "ExitCommand.h"
#include "Window.h"
#include "Game.h"


#define FPS_LIMIT 1.0/60.0

int main()
{
    Window window;
    Renderer renderer(window.width, window.height);
    Player player;
    Game game(player);
    std::vector<std::tuple<int, Command*>> commandLst = {
        std::make_tuple(GLFW_KEY_W,     new MoveCommand(game, MoveCommand::FORWARD)),
        std::make_tuple(GLFW_KEY_S,     new MoveCommand(game, MoveCommand::BACKWARD)),
        std::make_tuple(GLFW_KEY_A,     new MoveCommand(game, MoveCommand::LEFT)),
        std::make_tuple(GLFW_KEY_D,     new MoveCommand(game, MoveCommand::RIGHT)),
        std::make_tuple(GLFW_KEY_LEFT_SHIFT,        new WalkCommand(game)),
        std::make_tuple(GLFW_KEY_LEFT_CONTROL,      new CrouchCommand(game)),
        std::make_tuple(GLFW_MOUSE_BUTTON_LEFT,     new ShootCommand(game)),
        std::make_tuple(GLFW_KEY_ESCAPE,new ExitCommand (game))
    };
    InputManager input(commandLst, player);
    window.setKeyCallbacks(&input);

    double frameTime = glfwGetTime();
    while (!window.shouldClose() && game.isRunning())
    {
        double elapsedTime = glfwGetTime() - frameTime;
        window.pollEvents();
        if(elapsedTime >= FPS_LIMIT)
        {
            game.update();
            input.handleInput();
            renderer.draw(game.scene);
            window.swapBuffers();
            frameTime = glfwGetTime();
        }
    }

    return 0;
}
