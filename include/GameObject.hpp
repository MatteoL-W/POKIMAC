#ifndef FLAG_GAME
#define FLAG_GAME

#include <iostream>
#include "Game.hpp"

class GameObject {

public:
    GameObject(const std::string textureSheet, int x, int y);

    ~GameObject();

    void update();

    void render();

private:
    int xPosition;
    int yPosition;

    SDL_Texture *objectTexture;
    SDL_Rect srcRect, dstRect;
};

#endif