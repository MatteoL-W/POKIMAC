#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/AttacksFlag.hpp"
#include "../include/AttackInterface.hpp"
#include "../include/Colors.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"

Text *text2 = new Text();

// (cf. AttackFlags.hpp)
// Charge is the attack for TYPE_NORMAL (0)
// Tranch'Herbe is the attack for TYPE_PLANT (1)
// ...
std::string attacks[TYPES_LENGTHS] = {
    "Charge",
    "Tranch'Herbe",
    "Vibraqua",
    "Rebondifeu"
};

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