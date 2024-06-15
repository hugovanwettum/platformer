#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(const char* title, int width, int height);
    void clear();
    void present();
    void cleanup();
    SDL_Renderer* getRenderer() const;

    // Drawing text
    bool loadFont(const std::string& path);
    SDL_Texture* printString(const std::string& text, float scale);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* fontTexture;
    SDL_Texture* bitmapFont; // Add bitmapFont for the font texture
    int fontCharWidth;
    int fontCharHeight;
    std::unordered_map<char, SDL_Rect> charMap;
};

#endif
