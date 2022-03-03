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

    void drawPokemon(Pokemon *pokemon, int x, int y, bool enemy);

    void drawHealthPoint(Pokemon *pokemon, int x, int y, bool enemy);

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
    static bool isWaitingForPokemon() { return state == "pokemonChoice"; };

    /**
     * @brief When the state is 'waitingForAttack'
     * @return
     */
    static bool isWaitingForAttack() { return state == "waitingForAttack"; };

    /**
     * @brief When the state is 'postAttack'
     * @return
     */
    static bool isWaitingForActionPostAttack() { return state == "postAttack"; };

    /**
     * @brief When the state is 'enemysTurn'
     * @return
     */
    static bool isWaitingForEnemyTurn() { return state == "enemysTurn"; };

    void enemysTurn();

    void win();

    void lose();

    static std::string state;

    static int damagePokemon;

    static int damageEnemy;

private:
    Game *game;

    Pokemon *enemyPokemon;

    Pokemon *pokemon;

    SDL_Texture *sceneBackgroundTexture;

    SDL_Texture *pokemonPlatformTexture;

    SDL_Rect destPokemon, srcPokemon, destPlatform;
};
