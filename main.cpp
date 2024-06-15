#include <iostream>
#include "Constants.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Game.h"

int main(int argc, char* args[]) {
    Game game;

    if (!game.init("Platformer", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return -1;
    }

    game.run();

    game.cleanup();

    return 0;
}
