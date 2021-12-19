#pragma once

#include <iostream>

const int MAX_POKEMON = 1;

class Pokemon {
public:
    Pokemon(int pokemonId = rand() % MAX_POKEMON);

    ~Pokemon();

    std::string getName() { return name; };
private:
    std::string name;
    int health_point;
    int attack;
    int defense;
    int sprite_x;
    int sprite_y;
    int type[2];
};
