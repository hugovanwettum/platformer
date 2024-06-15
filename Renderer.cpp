#include "Renderer.h"

Renderer::Renderer()
    : window(nullptr), renderer(nullptr), bitmapFont(nullptr), fontCharWidth(6), fontCharHeight(8) {}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer() const {
    return renderer;
}

void Renderer::cleanup() {
    if (bitmapFont) {
        SDL_DestroyTexture(bitmapFont);
        bitmapFont = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}

bool Renderer::loadFont(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load font texture! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    bitmapFont = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!bitmapFont) {
        std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Assuming a grid of 16x6 characters in the bitmap font for the ASCII range 32-127
    int columns = 16;
    int firstChar = 32; // ASCII value of ' '
    int totalChars = 96; // ASCII 32 to 127

    for (int i = 0; i < totalChars; ++i) {
        char c = static_cast<char>(firstChar + i);
        int x = (i % columns) * fontCharWidth;
        int y = (i / columns) * fontCharHeight;
        SDL_Rect rect = { x, y, fontCharWidth, fontCharHeight };
        charMap[c] = rect;
    }

    return true;
}

SDL_Texture* Renderer::printString(const std::string& text, float scale) {
    int maxWidth = 0;
    int numLines = 1;
    int currentWidth = 0;

    for (const char& c : text) {
        if (c != '\n') {
            currentWidth++;
        } else {
            numLines++;
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
            currentWidth = 0;
        }
    }

    if (currentWidth > maxWidth) {
        maxWidth = currentWidth;
    }

    int textWidth = static_cast<int>(maxWidth * fontCharWidth * scale);
    int textHeight = static_cast<int>(numLines * fontCharHeight * scale);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textWidth, textHeight);
    if (!texture) {
        std::cerr << "Failed to create texture for string! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // Ensure blending mode is set
    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // RGBA with alpha = 0 (fully transparent)
    SDL_RenderClear(renderer);

    int x = 0;
    int y = 0;
    for (const char& c : text) {
        if (c != '\n') {
            auto it = charMap.find(c);
            if (it != charMap.end()) {
                SDL_Rect src = it->second;
                SDL_Rect dest = { x, y, static_cast<int>(fontCharWidth * scale), static_cast<int>(fontCharHeight * scale) };
                SDL_RenderCopy(renderer, bitmapFont, &src, &dest);
            }
            x += static_cast<int>(fontCharWidth * scale);
        } else {
            x = 0;
            y += static_cast<int>(fontCharHeight * scale);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
    return texture;
}
