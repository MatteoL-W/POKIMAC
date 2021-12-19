#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Pokemon.hpp"

Pokemon* pokemon = nullptr;

//TODO:dégager ça dans un fichier externe
int first_level[Map::MAP_HEIGHT][Map::MAP_WIDTH]{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/**
 * @brief Constructor of the Map object
 */
Map::Map() {
    tilesetMapTexture = IMG_LoadTexture(Game::renderer, "assets/tileset_map_texture.png");
    playerMapTexture = IMG_LoadTexture(Game::renderer, "assets/ethan_sprite.png");
    pokemonMapTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");

    loadMap(first_level);

    srcTexture.x = srcTexture.y = 0;
    srcTexture.w = destTexture.w = 32;
    srcTexture.h = destTexture.h = 32;
    destTexture.x = destTexture.y = 0;

    srcPokemon = srcTexture;
    destPokemon = destTexture;

    srcPlayer.h = srcPlayer.w = 64;
    destPlayer.h = destPlayer.w = 32;
}

Map::~Map() {

}

/**
 * @Brief Copy the external map into our map system
 * @param array
 */
void Map::loadMap(int array[Map::MAP_HEIGHT][Map::MAP_WIDTH]) {
    SDL_memmove(mapArray, array, sizeof(mapArray));

    pokemon = new Pokemon;
    mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;
    mapArray[MAP_PLAYER_Y+2][MAP_PLAYER_X] = MAP_POKEMON_CARAPUCE;
}

/**
 * @brief Draw the map
 */
void Map::drawMap() {
    int cellType = 0;

    for (int row = 0; row < Map::MAP_HEIGHT; row++) {
        for (int column = 0; column < Map::MAP_WIDTH; column++) {
            cellType = first_level[row][column];
            destTexture.x = destPlayer.x = destPokemon.x = column * 32;
            destTexture.y = destPlayer.y = destPokemon.y = row * 32;

            switch (cellType) {
                case MAP_WATER:
                    srcTexture.x = 64;
                    break;
                case MAP_GRASS:
                    srcTexture.x = 32;
                    break;
                case MAP_DIRT:
                    srcTexture.x = 0;
                    break;
                default:
                    break;
            }

            SDL_RenderCopy(Game::renderer, tilesetMapTexture, &srcTexture, &destTexture);

            if (mapArray[row][column] == MAP_PLAYER) {
                SDL_RenderCopy(Game::renderer, playerMapTexture, &srcPlayer, &destPlayer);
            }

            if (mapArray[row][column] >= 20 && mapArray[row][column] <= 40) {
                SDL_RenderCopy(Game::renderer, pokemonMapTexture, &srcPokemon, &destPokemon);
            }
        }
    }
}

/**
 * @brief Player move down, up, right or left
 * @param direction
 */
void Map::updatePlayerPosition(int direction) {
    int xOperator = 0;
    int yOperator = 0;

    switch (direction) {
        case MOVE_DOWN:
            srcPlayer.y = 64 * 0;
            yOperator = 1;
            break;

        case MOVE_UP:
            srcPlayer.y = 64 * 3;
            yOperator = -1;
            break;

        case MOVE_RIGHT:
            srcPlayer.y = 64 * 2;
            xOperator = 1;
            break;

        case MOVE_LEFT:
            srcPlayer.y = 64 * 1;
            xOperator = -1;
            break;

        default:
            break;
    }

    int futurePlayerCellTexture = mapArray[MAP_PLAYER_Y + yOperator][MAP_PLAYER_X + xOperator];

    if (futurePlayerCellTexture >= 1 && futurePlayerCellTexture <= 10) {
        mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = first_level[MAP_PLAYER_Y][MAP_PLAYER_X];
        MAP_PLAYER_Y = MAP_PLAYER_Y + yOperator;
        MAP_PLAYER_X = MAP_PLAYER_X + xOperator;
        mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;
    }
}

void Map::updatePlayerSprite() {
    int speed = 100;
    int frames = 4;
    srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

void Map::updatePlayerSpriteToDefault() {
    srcPlayer.x = 0;
}