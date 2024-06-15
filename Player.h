#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Constants.h"

class Player {
public:
    Player(float x, float y);
    ~Player();

    void handleEvent(SDL_Event& e);
    void move(float deltaTime);
    void render(SDL_Renderer* renderer);
private:
    float posX, posY; // Position in meters
    float velX, velY; // Velocity in meters per second
    SDL_Rect playerRect;
    bool isJumping;

    static constexpr float PLAYER_VEL = 5.0f; // Horizontal velocity in meters per second
    static constexpr float GRAVITY = 9.8f*1.5; // Gravity constant in meters per second squared
    static constexpr float JUMP_VELOCITY = -6.0f; // Jump velocity in meters per second
    static const int PLAYER_WIDTH = 50;
    static const int PLAYER_HEIGHT = 50;
    static constexpr float PIXELS_PER_METER = 100.0f; // Conversion factor from meters to pixels
};

#endif
