#pragma once

#include "MapTileFlag.hpp"
#include "Pokemon.hpp"

int getStartingPos(int playerPosition, int mapWidth, int centeredScale);

int getEndingPos(int playerPosition, int mapWidth, int centeredScale);

class Map {
public:
    static const int MAP_WIDTH = 25;
    static const int MAP_HEIGHT = 25;
    int MAP_CELL_WIDTH = 32;
    int MAP_CELL_HEIGHT = 32;

    int MAP_PLAYER_X = 8;
    int MAP_PLAYER_Y = 3;


    Map(bool isCameraCentered);

    ~Map();

    void loadMap(int array[MAP_HEIGHT][MAP_WIDTH]);

    void draw();

    void drawMap();

    void drawExtras();

    void toggleCamera();

    void updatePlayerPosition(int direction);

    void updatePlayerSprite();

    void updatePlayerSpriteToDefault();

    void placePokemon(Pokemon *pokemon, int x, int y);

    int[2] findTiles(int level[Map::MAP_HEIGHT][Map::MAP_WIDTH], int map_nb); 


    Pokemon* getInteractingPokemon() { return canAttack; }

private:
    Pokemon pokemon[2];
    SDL_Rect srcTexture, srcPlayer, srcPokemon, srcHealthCenter;
    SDL_Rect dest1by1, dest2by2;

    SDL_Texture *tilesetMapTexture;
    SDL_Texture *playerMapTexture;
    SDL_Texture *pokemonMapTexture;
    SDL_Texture *HealthCenterMapTexture;

    int mapArray[MAP_HEIGHT][MAP_WIDTH];

    Pokemon* canAttack;

    bool centeredCamera;
    int startingX, startingY, endingX, endingY;

        //..... (positions que findTiles trouve)
    //int TILES_X;
    //int TILES_Y;
};