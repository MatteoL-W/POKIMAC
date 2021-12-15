#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"

GameObject::GameObject(const std::string textureSheet, int x, int y) {
    objectTexture = IMG_LoadTexture(Game::renderer, textureSheet.c_str());

    xPosition = x;
    yPosition = y;
}

GameObject::~GameObject() {
}

void GameObject::update() {
    xPosition++;
    yPosition++;

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.h = srcRect.h * 2;
    dstRect.w = srcRect.w * 2;
    dstRect.x = xPosition;
    dstRect.y = yPosition;
}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &dstRect);
}