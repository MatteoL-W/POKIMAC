#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"

GameObject::GameObject(const std::string textureSheet, SDL_Renderer* rendererParameter, int x, int y) {
    renderer = rendererParameter;
    objectTexture = IMG_LoadTexture(renderer, textureSheet.c_str());

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
    SDL_RenderCopy(renderer, objectTexture, &srcRect, &dstRect);
}