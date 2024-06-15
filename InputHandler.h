#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include "Player.h"

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    void update(Player& player);
    bool isQuitRequested() const;

private:
    bool quitRequested;
};

#endif
