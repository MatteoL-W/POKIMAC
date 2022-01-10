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
#include "../include/Pokemon.hpp"

Pokemon *pokemon = nullptr;
Pokemon *enemy = nullptr;

int SDL_KeysFrom1To6[6] = {
        SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
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

    // Choice of pokemon
    if (battle->isWaitingForPokemon() && event.type == SDL_KEYDOWN) {
        for (int i = 0; i < Game::inventoryLength; i++) {
            if (event.key.keysym.sym == SDL_KeysFrom1To6[i] && Game::inventory[i]->getHealthPoint() != 0) {
                battle->setPokemon(Game::inventory[i]);
                Battle::state = "waitingForAttack";
            }
        }

        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                game->changeInterfaceToExploration();
                break;
        }
    }

    // Choice of attack
    if (battle->isWaitingForAttack() && event.type == SDL_KEYDOWN) {
        pokemon = battle->getPokemon();
        enemy = battle->getEnemy();
        switch (event.key.keysym.sym) {
            case SDLK_e:
                // TODO: attack N°0
                // faire une méthode pour calculer le nb de hp enlevé
                // faire une méthode pour retirer sur l'objet le nombre d'hp du dessus
                // afficher les dégats de l'attaque dans le texte informatif
                // battle->enemysTurn();
                break;
            case SDLK_g:
                // TODO: attack N°1
                break;

            // là c'est des trucs de tests qu'on enlèvera à la fin
            case SDLK_k:
                // cheatcode
                enemy->kill();
                break;
            case SDLK_h:
                // ennemy's turn
                battle->enemysTurn();
                break;
            case SDLK_w:
                game->changeInterfaceToExplorationAndLevelUp();
                battle->win();
                break;
            case SDLK_l:
                battle->lose();
                break;
        }
    }

    // enemy's turn
    if (battle->isWaitingForAction() && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            //TODO: faire bouton pour poursuivre
        }
    }
}

/**
 * @brief Update objects in the exploration part
 */
void AttackInterface::update() {

}

/**
 * @brief Render the exploration part (map and objects)
 */
void AttackInterface::render() {
    SDL_RenderClear(Game::renderer);

    battle->draw();

    SDL_RenderPresent(Game::renderer);
}