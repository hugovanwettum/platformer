#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Constants.h"
#include "Tilemap.h"

class Player {
public:
    Player(float x, float y);
    ~Player();

    void handleEvent(SDL_Event& e);
    void move(float deltaTime, const Tilemap& tilemap);
    void render(SDL_Renderer* renderer);
    SDL_Rect getBoundingBox() const;

private:
    float posX, posY; // Position in meters
    float velX, velY; // Velocity in meters per second
    bool isJumping;
    SDL_Rect playerRect;

    bool checkCollision(float newX, float newY, const Tilemap& tilemap) const;


};

#endif
