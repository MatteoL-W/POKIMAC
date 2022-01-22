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
    bool keyIsAlreadyPressed = false;
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (event.type == SDL_KEYUP) {
        keyIsAlreadyPressed = false;
    }

    // Choice of pokemon
    if (battle->isWaitingForPokemon() && event.type == SDL_KEYDOWN) {
        if (!keyIsAlreadyPressed) {
            for (int i = 0; i < Game::inventoryLength; i++) {
                if (event.key.keysym.sym == SDL_KeysFrom1To6[i] && Game::inventory[i]->getHealthPoint() > 0) {
                    battle->setPokemon(Game::inventory[i]);
                    Battle::state = "waitingForAttack";
                }
            }
            keyIsAlreadyPressed = true;
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
        if (!keyIsAlreadyPressed) {
            pokemon = battle->getPokemon();
            enemy = battle->getEnemy();
            /*if (pokemon->getHealthPoint() <= 0) {
                battle->lose();
                if (Game::level == 5 ) {
                    if (Battle::state == "waitingForMew") {
                        inventoryText->create("Vous avez debloque un Pokemon !", WhiteColor, "Press");
                        newPokemonText->create("Appuyer sur [I]", WhiteColor, "Press");
                        // newPokemonText->changeText("Vous avez debloque un Pokemon !");
                        // inventoryText->changeText("Appuyer sur [I]");
                        newPokemonText->changeDestRect(86, 485);
                        newPokemonText->draw();
                        inventoryText->changeDestRect(86, 580);
                        inventoryText->draw();
                    }
                }
                return;
            }*/

            switch (event.key.keysym.sym) {
                case SDLK_e:
                    Battle::damageEnemy = pokemon->getAttackZero();
                    enemy->removeHealthPoint(Battle::damageEnemy);
                    Battle::state = "postAttack";
                    break;

                case SDLK_g:
                    Battle::damageEnemy = pokemon->getAttackZero() *
                                          enemy->getDamageCoeff(pokemon->Pokemon::getType(), enemy->Pokemon::getType());
                    enemy->removeHealthPoint(Battle::damageEnemy);
                    Battle::state = "postAttack";
                    break;


                    //cheatcodes
                case SDLK_k:
                    enemy->kill();
                    break;
                case SDLK_n:
                    enemy->updateHealthPoint(enemy->getHealthPoint() - 10);
                    break;
                case SDLK_p:
                    battle->enemysTurn();
                    break;
            }

            keyIsAlreadyPressed = true;
        }
    }

    if (battle->isWaitingForActionPostAttack() && event.type == SDL_KEYDOWN) {
        if (!keyIsAlreadyPressed) {
            battle->enemysTurn();
            keyIsAlreadyPressed = true;
        }
    }

    if (battle->isWaitingForEnemyTurn() && event.type == SDL_KEYDOWN) {
        if (!keyIsAlreadyPressed) {
            if (pokemon->getHealthPoint() <= 0) {
                battle->lose();
                return;
            }
            Battle::state = "waitingForAttack";
            keyIsAlreadyPressed = true;
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

/**
 * @brief Return true if the attack interface is active
 * @return
 */
bool AttackInterface::isActive() {
    if (game->attacking())
        return true;
    return false;
}
