#pragma once

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

    void drawPokemon(Pokemon *pokemon, int x, int y);

    void drawDialog();

    void setEnemy(Pokemon *enemy) { Battle::enemyPokemon = enemy; };

private:
    Pokemon *enemyPokemon;

    Pokemon *pokemon;

    SDL_Texture *sceneBackgroundTexture;
    SDL_Texture *pokemonsTexture;
    SDL_Texture *pokemonPlatformTexture;
};
