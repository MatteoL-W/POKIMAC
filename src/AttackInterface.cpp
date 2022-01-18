#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <time.h>
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

            switch (event.key.keysym.sym) {
                case SDLK_e:
                    // TODO: attack N°0
                    // faire une méthode pour calculer le nb de hp enlevé (en enlevant des HP fixes dans un premier temps puis prendre en compte le type par la suite)
                    //<<<<faire une méthode pour retirer sur l'objet le nombre d'hp du dessus (genre pokemon->removeHealthPoints(int hp) où ça enlève les PV voulus)
                    // afficher les dégats de l'attaque dans le texte informatif
                    // battle->enemysTurn();
                    Battle::damageEnemy = pokemon->getAttackZero();
                    enemy->removeHealthPoint(Battle::damageEnemy);
                    Battle::state = "postAttack";
                    break;

                case SDLK_g:
                    // TODO: attack N°1
                    Battle::damageEnemy = pokemon->getAttackZero() * enemy->getDamageCoeff(pokemon->Pokemon::getType(), enemy->Pokemon::getType());
                    enemy->removeHealthPoint(Battle::damageEnemy);
                    Battle::state = "postAttack";
                    break;


                    //cheatcodes
                case SDLK_k:
                    // appuyer sur K pour mettre les HP de l'adversaire à 0
                    //enemy->kill();
                    enemy->kill();
                    break;
                case SDLK_n:
                    enemy->updateHealthPoint(enemy->getHealthPoint() - 10);
                    break;
                case SDLK_p:
                    // appuyer sur P pour passer au tour de l'ennemi
                    battle->enemysTurn();
                    break;
            }

            keyIsAlreadyPressed = true;
        }
    }

    // enemy's turn

    if (battle->isWaitingForActionPostAttack() && event.type == SDL_KEYDOWN) {
        if (!keyIsAlreadyPressed) {
            battle->enemysTurn();
            keyIsAlreadyPressed = true;
        }
    }

    if (battle->isWaitingForEnemyTurn() && event.type == SDL_KEYDOWN) {
        if (!keyIsAlreadyPressed) {

            //------------------Test pour que l'ennemi nous tue pas trop vite :

            //SOIT attaque exactement comme notre pokemon :
            //Battle::damagePokemon = enemy->getAttackZero() * pokemon->getDamageCoeff(enemy->Pokemon::getType(), pokemon->Pokemon::getType());

            //SOIT attaque comme nous si il est moins fort, et attaque normale si il est trop fort
            if (pokemon->getDamageCoeff(enemy->Pokemon::getType(), pokemon->Pokemon::getType()) <= 1) {
                Battle::damagePokemon = enemy->getAttackZero() * pokemon->getDamageCoeff(enemy->Pokemon::getType(), pokemon->Pokemon::getType());
            }
            else {
                Battle::damagePokemon = enemy->getAttackZero();
            }

            pokemon->removeHealthPoint(Battle::damagePokemon);

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

