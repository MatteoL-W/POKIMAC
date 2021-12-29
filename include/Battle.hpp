#pragma once

#include "AttackInterface.hpp"
#include "Pokemon.hpp"

class Battle {
public:
    Battle(Pokemon *enemy, Pokemon *myPokemon);

    ~Battle();

    void load();

    void draw();

private:
    Pokemon *enemyPokemon;

    Pokemon *pokemon;
};
