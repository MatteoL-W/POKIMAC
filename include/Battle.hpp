#pragma once

#include <iostream>
#include "AttackInterface.hpp"
#include "Pokemon.hpp"
#include "Text.hpp"

class Battle {
public:
    Battle(Pokemon *enemy, Pokemon *myPokemon);

    ~Battle();

    void load();

    void draw();

    void drawBackground();

    void drawPokemonGraphics();

    void drawPokemon(Pokemon *pokemon, int x, int y);

    void drawHealthPoint(Pokemon *pokemon, int x, int y);

    void drawDialog();

    void setPokemon(Pokemon *pokemon) { Battle::pokemon = pokemon; };

    void setEnemy(Pokemon *enemy) { Battle::enemyPokemon = enemy; };

    bool isWaitingForPokemon() {
        if (state == "pokemonChoice") {
            return true;
        }
        return false;
    }

    static std::string state;

private:

    Pokemon *enemyPokemon;

    Pokemon *pokemon;

    SDL_Texture *sceneBackgroundTexture;
    SDL_Texture *pokemonsTexture;
    SDL_Texture *pokemonPlatformTexture;
};
