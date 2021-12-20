#pragma once

#include "MapTileFlag.hpp"
#include "Pokemon.hpp"

class Map {
public:
    static const int MAP_WIDTH = 25;
    static const int MAP_HEIGHT = 20;
    int MAP_PLAYER_X = 8;
    int MAP_PLAYER_Y = 3;

    Map();

    ~Map();

    void loadMap(int array[MAP_HEIGHT][MAP_WIDTH]);

    void drawMap();

    void updatePlayerPosition(int direction);

    void updatePlayerSprite();

    void updatePlayerSpriteToDefault();

    void placePokemon(Pokemon* pokemon, int x, int y);

private:
    Pokemon pokemon[2];
    SDL_Rect srcTexture, srcPlayer, srcPokemon;
    SDL_Rect destTexture;
    SDL_Texture *tilesetMapTexture;
    SDL_Texture *playerMapTexture;
    SDL_Texture *pokemonMapTexture;
    int mapArray[MAP_HEIGHT][MAP_WIDTH];
};