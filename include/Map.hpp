#pragma once

#include "MapTileFlag.hpp"
#include "Pokemon.hpp"
#include "Game.hpp"

int getStartingPos(int playerPosition, int mapWidth, int centeredScale);

int getEndingPos(int playerPosition, int mapWidth, int centeredScale);

int getRandomNumberTo(int max);

class Map {
public:
    Map(bool isCameraCentered);

    ~Map();

    static const int MAP_WIDTH = 25;

    static const int MAP_HEIGHT = 25;

    void defineSrcRectsValues();

    void defineDestRectsValues();

    void loadMap(const int array[MAP_HEIGHT][MAP_WIDTH]);

    void loadPokemons();

    void draw();

    void drawMap();

    void drawExtras();

    void drawPokemon(int i);

    void toggleCamera();

    void updatePlayerPosition(int direction);

    void updatePlayerSprite();

    void updatePlayerSpriteToDefault();

    void placePokemon(Pokemon *pokemon, int x, int y);

    int *findTiles(const int level[Map::MAP_HEIGHT][Map::MAP_WIDTH], int map_nb);

    void drawHealthCenter();

    Pokemon *getInteractingPokemon() { return canAttack; }

    bool getInteractingHealthCenter() { return canBeCured; }

    static const int BOSS_LEVEL = 5;

    float MAP_CELL_WIDTH = 32 * Game::SCALE_CAMERA;

    float MAP_CELL_HEIGHT = 32 * Game::SCALE_CAMERA;

    int MAP_PLAYER_X = 8;

    int MAP_PLAYER_Y = 3;

private:
    Pokemon *canAttack;

    Pokemon pokemon[MAX_POKEMONS_POKEDEX];

    SDL_Rect srcTexture, srcPlayer, srcPokemon, srcHealthCenter;

    SDL_Rect dest1by1, dest2by2;

    SDL_Texture *tilesetMapTexture;

    SDL_Texture *HealthCenterMapTexture;

    int mapArray[MAP_HEIGHT][MAP_WIDTH];

    bool canBeCured;

    bool centeredCamera;

    int startingX, startingY, endingX, endingY;
};
