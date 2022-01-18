#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Pokemon.hpp"
#include "../include/AttacksFlag.hpp"

/**
 * @brief Initialize a new pokemon set from the txt database
 * @param isWild
 * @param pokemonId
 */
Pokemon::Pokemon(int id, bool isWild) {
    // On récupère le contenu du fichier database/pokemon.txt, on le choisi en fonction du paramètre pokemonId
    // S'il n'est pas renseigné, il est assigné aléatoire (voir Pokemon.hpp)
    // On boucle sur chaque ligne jusqu'à arriver au pokemonId
    // Le pokemon assigné à cette ligne est ainsi créée dans le nouvel objet pokemon initié
    //TODO: essayer de ne pas faire boucler mais de choper directement la ligne
    std::ifstream pokemon_db("database/pokemon.txt");

    if (pokemon_db) {
        int lines = 0;
        int max_hp, att, def, x_spr, y_spr, type1;
        std::string pokename;

        while (pokemon_db >> pokename >> max_hp >> att >> def >> x_spr >> y_spr >> type1) {
            if (lines == id) {
                name = pokename;
                max_health_point = max_hp;
                health_point = max_hp;
                attack = att;
                defense = def;
                sprite_x_o = x_spr;
                sprite_x = x_spr;
                sprite_y = y_spr;
                type = type1;
                wild = isWild;

                break;
            }
            lines++;
        }

        Game::pokedex[id] = this;
    }
}

Pokemon::~Pokemon() {
}

/**
 * @brief Assign the pokemon to a point on the map
 * @param x
 * @param y
 */
void Pokemon::setCoordinates(int x, int y) {
    column = x;
    row = y;
}

void Pokemon::removeHealthPoint(int health_point) {
    Pokemon::health_point = (Pokemon::health_point - health_point < 0 ) ? 0 : Pokemon::health_point - health_point;
}

/**
 * @brief Update the sprite of the pokemon
 */
void Pokemon::updateSprite() {
    int speed = 200;
    int frames = 3;
    sprite_x = getOriginalXSpriteCoordinate() + (32 * static_cast<int>((SDL_GetTicks() / speed) % frames));
}


float Pokemon::getDamageCoeff(int attacker_type, int attacked_type) {
    float coefficient = 1;
    if (attacker_type == attacked_type) {
        coefficient = 0.5;
    }
    if (attacker_type == TYPE_PLANT) { 
        if (attacked_type == TYPE_FIRE) { 
            coefficient = 0.5;
        }
        if (attacked_type == TYPE_ROCK) {
            coefficient = 2;
        }     
    }
    if (attacker_type == TYPE_WATER) { 
        if (attacked_type == TYPE_PLANT) { 
            coefficient = 0.5;
        }
        if (attacked_type == TYPE_FIRE) {
            coefficient = 2;
        }
        if (attacked_type == TYPE_ROCK) {
            coefficient = 2;
        }     
    }
    if (attacker_type == TYPE_FIRE) { 
        if (attacked_type == TYPE_PLANT) { 
            coefficient = 2;
        }
        if (attacked_type == TYPE_WATER) {
            coefficient = 0.5;
        }
        if (attacked_type == TYPE_ICE) {
            coefficient = 2;
        }     
    }
    if (attacker_type == TYPE_ROCK) { 
        if (attacked_type == TYPE_PLANT) { 
            coefficient = 0.5;
        }
        if (attacked_type == TYPE_FIRE) {
            coefficient = 2;
        }
        if (attacked_type == TYPE_ICE) {
            coefficient = 2;
        }     
    }
    if (attacker_type == TYPE_ICE) { 
        if (attacked_type == TYPE_PLANT) { 
            coefficient = 2;
        }
        if (attacked_type == TYPE_WATER) {
            coefficient = 0.5;
        }
        if (attacked_type == TYPE_FIRE) {
            coefficient = 0.5;
        }     
    }           
    return coefficient;
}