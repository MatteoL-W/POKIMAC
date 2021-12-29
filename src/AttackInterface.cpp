#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/AttackInterface.hpp"

Text *text2 = new Text();

/**
 * @brief Handle SDL Events in the exploration part
 */
void AttackInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }
}

/**
 * @brief Update objects in the exploration part
 */
void AttackInterface::update() {
    text2->create("Font testing", RedColor, "Press");
    text2->changeText("Testttttttttttttttttttttttttttttttttttttttttt");
}

/**
 * @brief Render the exploration part (map and objects)
 */
void AttackInterface::render() {
    SDL_RenderClear(Game::renderer);

    text2->draw();

    SDL_RenderPresent(Game::renderer);
}