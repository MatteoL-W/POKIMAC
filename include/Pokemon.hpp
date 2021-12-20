#pragma once

#include <iostream>

const int MAX_POKEMON = 1;

class Pokemon {
public:
    Pokemon(bool wild = true, int pokemonId = rand() % MAX_POKEMON);

    ~Pokemon();

    std::string getName() { return name; };

    void setCoordinates(int x, int y);

    int getXSpriteCoordinate() { return sprite_x; };

    int getYSpriteCoordinate() { return sprite_y; };

    int getRow() { return row; };

    int getColumn() { return column; };

private:
    std::string name;
    int health_point;
    int attack;
    int defense;
    int sprite_x;
    int sprite_y;
    int type[2];

    bool wild;
    int column;
    int row;
};
