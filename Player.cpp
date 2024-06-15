#include "Player.h"

Player::Player(float x, float y)
    : posX(x / PIXELS_PER_METER), posY(y / PIXELS_PER_METER), velX(0), velY(0), isJumping(false) {
    playerRect = { static_cast<int>(posX * PIXELS_PER_METER), static_cast<int>(posY * PIXELS_PER_METER), PLAYER_WIDTH, PLAYER_HEIGHT };
}

Player::~Player() {}

void Player::handleEvent(SDL_Event& e) {
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                if (!isJumping) {
                    velY = JUMP_VELOCITY;
                    isJumping = true;
                }
                break;
            case SDLK_LEFT: velX = -PLAYER_VEL; break;
            case SDLK_RIGHT: velX = PLAYER_VEL; break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                if (velX < 0) velX = 0;
                break;
            case SDLK_RIGHT:
                if (velX > 0) velX = 0;
                break;
        }
    }
}

void Player::move(float deltaTime, const Tilemap& tilemap) {
    // Apply gravity to vertical velocity
    velY += GRAVITY * deltaTime;

    // Calculate new position
    float newX = posX + velX * deltaTime;
    float newY = posY + velY * deltaTime;

    // Check for collisions
    if (!checkCollision(newX, posY, tilemap)) {
        posX = newX;
    } else {
        velX = 0; // Stop horizontal movement on collision
    }
    if (!checkCollision(posX, newY, tilemap)) {
        posY = newY;
    } else {
        velY = 0; // Stop vertical movement on collision
        isJumping = false; // Allow jumping again
    }

    // Keep the player in bounds
    if (posX < 0) {
        posX = 0;
        velX = 0; // Stop horizontal movement when hitting the left bound
    } else if (posX > (SCREEN_WIDTH - PLAYER_WIDTH) / PIXELS_PER_METER) {
        posX = (SCREEN_WIDTH - PLAYER_WIDTH) / PIXELS_PER_METER;
        velX = 0; // Stop horizontal movement when hitting the right bound
    }

    if (posY < 0) {
        posY = 0;
        velY = 0; // Stop vertical movement when hitting the top bound
    } else if (posY > (SCREEN_HEIGHT - PLAYER_HEIGHT) / PIXELS_PER_METER) {
        posY = (SCREEN_HEIGHT - PLAYER_HEIGHT) / PIXELS_PER_METER;
        velY = 0; // Stop vertical movement when hitting the bottom bound
        isJumping = false; // Allow jumping again
    }

    playerRect.x = static_cast<int>(posX * PIXELS_PER_METER);
    playerRect.y = static_cast<int>(posY * PIXELS_PER_METER);
}

void Player::render(SDL_Renderer* renderer) {
    // Set the draw color to blue for the player
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &playerRect);
}

bool Player::checkCollision(float newX, float newY, const Tilemap& tilemap) const {
    SDL_Rect newRect = { static_cast<int>(newX * PIXELS_PER_METER), static_cast<int>(newY * PIXELS_PER_METER), playerRect.w, playerRect.h };
    return tilemap.checkCollision(newRect);
}
