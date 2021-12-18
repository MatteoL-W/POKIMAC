#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Game.hpp"
#include "../include/Map.hpp"

//TODO:dégager ça dans un fichier externe
int first_level[Map::MAP_HEIGHT][Map::MAP_WIDTH]{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

    loadMap(first_level);

    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;

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

    mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;
}

/**
 * @brief Draw the map
 */
void Map::drawMap() {
    int cellType = 0;

    for (int row = 0; row < Map::MAP_HEIGHT; row++) {
        for (int column = 0; column < Map::MAP_WIDTH; column++) {
            cellType = first_level[row][column];
            dest.x = destPlayer.x = column * 32;
            dest.y = destPlayer.y = row * 32;

            switch (cellType) {
                case MAP_WATER:
                    src.x = 64;
                    break;
                case MAP_GRASS:
                    src.x = 32;
                    break;
                case MAP_DIRT:
                    src.x = 0;
                    break;
                default:
                    break;
            }

            SDL_RenderCopy(Game::renderer, tilesetMapTexture, &src, &dest);

            if (mapArray[row][column] == MAP_PLAYER) {
                SDL_RenderCopy(Game::renderer, playerMapTexture, &srcPlayer, &destPlayer);
            }
        }
    }
}

/**
 * @brief Player move down, up, right or left
 * @param direction
 */
void Map::updatePlayer(int direction) {
    int xOperator = 0;
    int yOperator = 0;

    switch (direction) {
        case MOVE_DOWN:
            yOperator = 1;
            break;

        case MOVE_UP:
            yOperator = -1;
            break;

        case MOVE_RIGHT:
            xOperator = 1;
            break;

        case MOVE_LEFT:
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