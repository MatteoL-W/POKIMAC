#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"

/**
 * @brief Construct the Game Object
 * @param textureSheet
 * @param x
 * @param y
 */
GameObject::GameObject(const std::string textureSheet, int x, int y) {
    objectTexture = IMG_LoadTexture(Game::renderer, textureSheet.c_str());

    xPosition = x;
    yPosition = y;
}

GameObject::~GameObject() {
}

/**
 * @brief Update the GameObject positions
 */

void GameObject::update() {
    srcRect.h = srcRect.w = 64;
    srcRect.x = srcRect.y = 0;

    dstRect.h = dstRect.w = 32;
    dstRect.x = xPosition;
    dstRect.y = yPosition;
}

/**
 * @brief Render the GameObject
 */
void GameObject::render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &dstRect);
}