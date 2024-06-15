#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 736;

static constexpr float PLAYER_VEL = 5.0f; // Horizontal velocity in meters per second
static constexpr float GRAVITY = 9.8f*1.5; // Gravity constant in meters per second squared
static constexpr float JUMP_VELOCITY = -8.0f; // Jump velocity in meters per second
static const int PLAYER_WIDTH = 50;
static const int PLAYER_HEIGHT = 50;
static constexpr float PIXELS_PER_METER = 100.0f; // Conversion factor from meters to pixels

#endif // CONSTANTS_H

