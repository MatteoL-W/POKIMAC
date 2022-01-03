#pragma once

#include "AttackInterface.hpp"
#include "Pokemon.hpp"

class Battle {
public:
    Battle(Pokemon *enemy, Pokemon *myPokemon);

    ~Battle();

    void load();

    void draw();

    void drawBackground();

    void drawPokemons();

    void drawDialog();

    void setEnemy(Pokemon *enemy) { Battle::enemyPokemon = enemy; };

private:
    Pokemon *enemyPokemon;

    Pokemon *pokemon;

    SDL_Texture *sceneBackgroundTexture;
    SDL_Texture *pokemonsTexture;
    SDL_Texture *pokemonPlatformTexture;
};
