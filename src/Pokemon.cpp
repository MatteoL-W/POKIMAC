#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Pokemon.hpp"
#include <fstream>
#include <sstream>
#include <string>

Pokemon::Pokemon(int pokemonId) {
    std::ifstream pokemon_db("database/pokemon.txt");

    if (pokemon_db) {
        int lines = 1;
        int hp, att, def, x_spr, y_spr, type1, type2;
        std::string pokename;

        while (pokemon_db >> pokename >> hp >> att >> def >> x_spr >> y_spr >> type1 >> type2)
        {
            if (lines == pokemonId) {
                name = pokename;
                health_point = hp;
                attack = att;
                defense = def;
                sprite_x = x_spr;
                sprite_y = y_spr;
                type[0] = type1;
                type[1] = type2;
                break;
            }
            lines++;
        }
    }
}

Pokemon::~Pokemon() {
}