#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <SDL.h>


class Tilemap{
public:
    Tilemap();
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& rect) const;

private:
    std::vector<std::vector<int>> tiles;
    int tileWidth;
    int tileHeight;
};


#endif
