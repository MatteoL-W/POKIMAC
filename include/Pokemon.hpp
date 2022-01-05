#pragma once

#include <iostream>

const int MAX_POKEMON = 2;

class Pokemon {
public:
    Pokemon(int id = (rand() % MAX_POKEMON), bool isWild = true);

    ~Pokemon();

    std::string getName() { return name; };

    void setCoordinates(int x, int y);

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
