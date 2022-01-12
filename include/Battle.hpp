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

    void setPokemon(Pokemon *pokemon) { Battle::pokemon = pokemon; };

    void setEnemy(Pokemon *enemy) { Battle::enemyPokemon = enemy; };

    Pokemon* getPokemon() { return pokemon; };

    Pokemon* getEnemy() { return enemyPokemon; };

    bool isWaitingForPokemon() {
        if (state == "pokemonChoice") {
            return true;
        }
        return false;
    }

    bool isWaitingForAttack() {
        if (state == "waitingForAttack") {
            return true;
        }
        return false;
    }

    bool isWaitingForAction() {
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
    SDL_Texture *pokemonsTexture;
    SDL_Texture *pokemonPlatformTexture;
};
