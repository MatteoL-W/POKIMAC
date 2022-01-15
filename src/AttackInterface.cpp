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
                Battle::state = "inactive";
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
                // faire une méthode pour calculer le nb de hp enlevé (en enlevant des HP fixes dans un premier temps puis prendre en compte le type par la suite)
                // faire une méthode pour retirer sur l'objet le nombre d'hp du dessus (genre pokemon->removeHealthPoints(int hp) où ça enlève les PV voulus)
                // afficher les dégats de l'attaque dans le texte informatif
                // battle->enemysTurn();
                break;
            case SDLK_g:
                // TODO: attack N°1
                break;

                //cheatcodes
            case SDLK_k:
                // appuyer sur K pour mettre les HP de l'adversaire à 0
                //enemy->kill();
                enemy->kill();
                break;
            case SDLK_n:
                enemy->updateHealthPoint(enemy->getHealthPoint()-10);
                break;
            case SDLK_p:
                // appuyer sur P pour passer au tour de l'ennemi
                battle->enemysTurn();
                break;
            case SDLK_l:
                battle->lose();
                break;
        }
    }

    // enemy's turn
    if (battle->isWaitingForAction() && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            //TODO: faire bouton pour poursuivre (je pense le faire)
        }
    }
}

/**
 * @brief Update objects in the exploration part
 */
void AttackInterface::update() {
    Pokemon *pokemon = battle->getPokemon();
    Pokemon *enemy = battle->getEnemy();

    enemy->updateSprite();
    if (pokemon != nullptr) {
        pokemon->updateSprite();
    }
}

/**
 * @brief Render the exploration part (map and objects)
 */
void AttackInterface::render() {
    SDL_RenderClear(Game::renderer);

    battle->draw();

    SDL_RenderPresent(Game::renderer);
}