#include <fstream>
#include "json.hpp"
#include "Tilemap.h"

Tilemap::Tilemap() {
    std::ifstream file("tilemap.json");
    nlohmann::json json;
    file >> json;

    tiles = json["tiles"].get<std::vector<std::vector<int>>>();
    tileWidth = json["tileWidth"];
    tileHeight = json["tileHeight"];
}

void Tilemap::render(SDL_Renderer* renderer) {
    for (int y = 0; y < tiles.size(); ++y) {
        for (int x = 0; x < tiles[y].size(); ++x) {
            int tileValue = tiles[y][x];

            SDL_Rect tileRect = { static_cast<int>(x * tileWidth), static_cast<int>(y * tileHeight), tileWidth, tileHeight };

            // If the tilemap value is nonzero, we draw a square there
            if (tileValue) {
                // Set the draw color to black for the blocks
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(renderer, &tileRect);
            }
        }
    }
}


bool Tilemap::checkCollision(const SDL_Rect& rect) const {
    int startX = rect.x / tileWidth;
    int startY = rect.y / tileHeight;
    int endX = (rect.x + rect.w) / tileWidth;
    int endY = (rect.y + rect.h) / tileHeight;

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            if (tiles[y][x] != 0) {
                SDL_Rect tileRect = { x * tileWidth, y * tileHeight, tileWidth, tileHeight };
                if (SDL_HasIntersection(&rect, &tileRect)) {
                    return true;
                }
            }
        }
    }
    return false;
}
