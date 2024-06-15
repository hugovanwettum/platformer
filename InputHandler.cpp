#include "InputHandler.h"

InputHandler::InputHandler() : quitRequested(false) {}

InputHandler::~InputHandler() {}

void InputHandler::update(Player& player) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quitRequested = true;
        }
        // Pass the event to the player to handle movement
        player.handleEvent(e);
    }
}

bool InputHandler::isQuitRequested() const {
    return quitRequested;
}
