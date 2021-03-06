#pragma once

#include <iostream>
#include <cmath>

const int POKEMON_AVAILABLE = 3;

class Pokemon {
public:
    Pokemon(int id = (rand() % POKEMON_AVAILABLE), bool isWild = true);

    ~Pokemon();

    void setCoordinates(int x, int y);

    void kill() { health_point = 0; };

    std::string getName() { return name; };

    int getOriginalXSpriteCoordinate() { return sprite_x_o; };

    int getXSpriteCoordinate() { return sprite_x; };

    int getYSpriteCoordinate() { return sprite_y; };

    int getRow() { return row; };

    int getColumn() { return column; };

    int getHealthPoint() { return health_point; };

    int getMaxHealthPoint() { return max_health_point; };

    int getType() { return type; };

    float getHealthPercent() { return (float) health_point / max_health_point * 100; };

    void updateHealthPoint(int new_health_point) { Pokemon::health_point = new_health_point; };

    void removeHealthPoint(int health_point);

    void heal() { Pokemon::health_point = Pokemon::max_health_point; };

    void updateSprite();

    float getDamageCoeff(int attacker_type, int attacked_type);

    int getAttackZero() { return floor(Pokemon::attack * 0.25); };


private:
    std::string name;

    int health_point;
    int max_health_point;
    int attack;
    int defense;
    int sprite_x;
    int sprite_x_o;
    int sprite_y;
    int type;

    bool wild;
    int column;
    int row;
};
