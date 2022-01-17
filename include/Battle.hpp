#pragma once

#include <iostream>
#include "Game.hpp"
#include "AttackInterface.hpp"
#include "Pokemon.hpp"
#include "Text.hpp"

class Battle {
public:
    Battle(Pokemon *enemy, Pokemon *myPokemon, Game *game);

    ~Battle();

    void load();

    void reload();

    void draw();

    void drawBackground();

    void drawPokemonGraphics();

    void drawPokemon(Pokemon *pokemon, int x, int y);

    void drawHealthPoint(Pokemon *pokemon, int x, int y);

    void drawDialog();
    void drawDialogPokemonChoice();
    void drawDialogAttackChoice();
    void drawDialogPostAttack();
    void drawDialogEnemyTurn();

    void setPokemon(Pokemon *pokemon) { Battle::pokemon = pokemon; };

    void setEnemy(Pokemon *enemy) { Battle::enemyPokemon = enemy; };

    Pokemon *getPokemon() { return pokemon; };

    Pokemon *getEnemy() { return enemyPokemon; };

    /**
     * @brief When the state is 'pokemonChoice'
     * @return
     */
    bool isWaitingForPokemon() {
        if (state == "pokemonChoice") {
            return true;
        }
        return false;
    }

    /**
     * @brief When the state is 'waitingForAttack'
     * @return
     */
    bool isWaitingForAttack() {
        if (state == "waitingForAttack") {
            return true;
        }
        return false;
    }

    /**
     * @brief When the state is 'postAttack'
     * @return
     */
    bool isWaitingForActionPostAttack() {
        if (state == "postAttack") {
            return true;
        }
        return false;
    }

    /**
     * @brief When the state is 'enemysTurn'
     * @return
     */
    bool isWaitingForEnemyTurn() {
        if (state == "enemysTurn") {
            return true;
        }
        return false;
    }

    void enemysTurn();

    void win();

    void lose();

    static std::string state;

private:
    Game *game;

    Pokemon *enemyPokemon;

    Pokemon *pokemon;

    SDL_Texture *sceneBackgroundTexture;
    SDL_Texture *pokemonPlatformTexture;
};
