#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"
#include "../include/Map.hpp"

GameObject* player = nullptr;
GameObject* enemy = nullptr;
Map* map = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}

void Game::init(const std::string title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        isRunning = true;

        player = new GameObject("assets/ethan_sprite.png", 0, 0);
        enemy = new GameObject("assets/ethan_sprite.png", 64, 64);
        map = new Map();

        //TODO:peut remove le render
        Game::render();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    player->update();
    enemy->update();
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();
    player->render();
    enemy->render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}