#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/ExplorationInterface.hpp"

Text *text = new Text();

/**
 * @brief Handle SDL Events in the exploration part
 */
void ExplorationInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN && map->getInteractingPokemon()) {
        switch (event.key.keysym.sym) {
            case SDLK_e:
                game->changeInterfaceToAttack(map->getInteractingPokemon());
                break;
        }
    }

    if (event.type == SDL_KEYDOWN && map->getInteractingHealthCenter()) {
        for (int i = 0; i < Game::inventoryLength; i++) {
            if (Game::inventory[i]->getHealthPoint() != Game::inventory[i]->getMaxHealthPoint()) {
                Game::inventory[i]->updateHealthPoint(Game::inventory[i]->getMaxHealthPoint());
            }
        }
    }


    // Si une touche est enfoncée, on vérifie si elle correspond à une touche assignée au mouvement (flèches et ZQSD)
    // On enclenche le déplacement si c'est le cas
    if (event.type == SDL_KEYDOWN) {
        map->updatePlayerSprite();
        switch (event.key.keysym.sym) { // Quelle touche est appuyée ?
            case SDLK_z:
            case SDLK_UP:
                map->updatePlayerPosition(MOVE_UP);
                break;
            case SDLK_q:
            case SDLK_LEFT:
                map->updatePlayerPosition(MOVE_LEFT);
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                map->updatePlayerPosition(MOVE_RIGHT);
                break;
            case SDLK_s:
            case SDLK_DOWN:
                map->updatePlayerPosition(MOVE_DOWN);
                break;
            case SDLK_m:
                map->toggleCamera();
            default:
                break;
        }
    }

    if (event.type == SDL_KEYUP) {
        map->updatePlayerSpriteToDefault();
    }
}

/**
 * @brief Update objects in the exploration part
 */
void ExplorationInterface::update() {
    text->create("", WhiteColor, "Press");

    if (map->getInteractingPokemon()) {
        text->changeText("Appuyer sur [E] pour interagir");
        text->changeDestRect(40, 750);
    }

    //§§§§

    if (map->getInteractingHealthCenter()) {
        text->changeText("Appuyer sur [E] pour soigner les Pokemons");
        text->changeDestRect(40, 750);
    }
}

/**
 * @brief Render the exploration part (map and objects)
 */
void ExplorationInterface::render() {
    SDL_RenderClear(Game::renderer);

    map->draw();

    if (map->getInteractingPokemon()) {
        text->draw();
    }

    //§§§§
    if (map->getInteractingHealthCenter()) {
        text->draw();
    }


    SDL_RenderPresent(Game::renderer);
}