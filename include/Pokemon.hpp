#pragma once

#include <iostream>

class Pokemon {
public:
    Pokemon();

    ~Pokemon();

private:
    int SPRITE_X, SPRITE_Y;
    std::string name;
    int health_point;
    int type[2];
    int attack;
    int defense;
};
