#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Map.hpp"
#include "../include/Pokemon.hpp"
#include <fstream>
#include <iostream>

/**
 * @brief Initialize a new pokemon set from the txt database
 * @param isWild, pokemonId
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
        int hp, att, def, x_spr, y_spr, type1, type2;
        std::string pokename;

        while (pokemon_db >> pokename >> hp >> att >> def >> x_spr >> y_spr >> type1 >> type2) {
            if (lines == id) {
                name = pokename;
                health_point = hp;
                attack = att;
                defense = def;
                sprite_x = x_spr;
                sprite_y = y_spr;
                type[0] = type1;
                type[1] = type2;
                wild = isWild;

                break;
            }
            lines++;
        }
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