#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "InputHandler.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void run();
    void cleanup();

private:
    Renderer renderer;
    InputHandler inputHandler;
    Player* player;
    bool running;
};

#endif
