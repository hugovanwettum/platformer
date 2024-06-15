#include "Game.h"
#include <stdio.h>
#include <string>

Game::Game() : running(false), player(nullptr) {}

Game::~Game() {
    cleanup();
}

bool Game::init(const char* title, int width, int height) {
    if (!renderer.init(title, width, height)) {
        return false;
    }
    // Load font map
    if (!renderer.loadFont("black_font.png")) {
        return false;
    }
    player = new Player(width / 2, height / 2);
    running = true;
    return true;
}

void Game::run() {
    //https://gafferongames.com/post/fix_your_timestep/
    const double dt = 1.0 / 60.0;
    double t = 0.0;
    double currentTime = SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();

    while (running) {
        double newTime = SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        // Handle input once per frame
        inputHandler.update(*player);
        if (inputHandler.isQuitRequested()) {
            running = false;
        }

        std::string deltaTimeStr;

        while (frameTime > 0.0) {
            float deltaTime = std::min(frameTime, dt);
            player->move(deltaTime); // Integrate state
            frameTime -= deltaTime;
            t += deltaTime;
            //std::cout << deltaTime << "\n";
            //deltaTimeStr = "FPS: " + std::to_string(1 / deltaTime); // Convert deltaTime to fps as a string
        }


        // Render once per frame
        renderer.clear();
        player->render(renderer.getRenderer());


        int textWidth, textHeight;
        /*
        // Create deltaTime text texture and render it
        SDL_Texture* deltaTimeTexture = renderer.printString(deltaTimeStr, 1.0f); // Adjust scale as needed
        SDL_QueryTexture(deltaTimeTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect deltaTimeRect = { 10, 10, textWidth, textHeight }; // Position it below the "Hello, world!" text
        SDL_RenderCopy(renderer.getRenderer(), deltaTimeTexture, NULL, &deltaTimeRect);
        SDL_DestroyTexture(deltaTimeTexture);
        */

        // Create text texture and render it
        SDL_Texture* textTexture = renderer.printString("Hello, world!", 3.2f);
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect dstRect = { 50, 50, textWidth, textHeight };
        SDL_RenderCopy(renderer.getRenderer(), textTexture, NULL, &dstRect);
        SDL_DestroyTexture(textTexture);





        renderer.present();

        // Optional: Add a delay to limit the frame rate if needed
        SDL_Delay(1);
    }
}

void Game::cleanup() {
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }
    renderer.cleanup();
}