#pragma once

#include <iostream>

const int POKEMON_AVAILABLE = 3;

class Pokemon {
public:
    Pokemon(int id = (rand() % POKEMON_AVAILABLE), bool isWild = true);

    ~Pokemon();

    std::string getName() { return name; };

    void setCoordinates(int x, int y);

    void kill() { health_point = 0; };

    int getXSpriteCoordinate() { return sprite_x; };

    int getYSpriteCoordinate() { return sprite_y; };

    int getRow() { return row; };

    int getColumn() { return column; };

    int getHealthPoint() { return health_point; };

    int getMaxHealthPoint() { return max_health_point; };

    int getType() { return type; };

private:
    std::string name;
    int health_point;
    int max_health_point;
    int attack;
    int defense;
    int sprite_x;
    int sprite_y;
    int type;

    bool wild;
    int column;
    int row;
};
