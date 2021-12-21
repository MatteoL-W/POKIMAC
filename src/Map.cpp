#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Pokemon.hpp"

Pokemon *bulbizarre = nullptr;
Pokemon *carapuce = nullptr;
int pokemonCounter = 20;

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

    srcTexture.x = srcTexture.y = 0;
    srcTexture.w = destTexture.w = 32;
    srcTexture.h = destTexture.h = 32;
    srcPlayer.h = srcPlayer.w = 64;
    srcPokemon = srcTexture;

    destTexture.x = destTexture.y = 0;

    Map::loadMap(first_level);
}

Map::~Map() {

}

/**
 * @Brief Copy the external map into our map system
 * @param array
 */
void Map::loadMap(int array[Map::MAP_HEIGHT][Map::MAP_WIDTH]) {
    // Copy of mapArray from first_level
    SDL_memmove(mapArray, array, sizeof(mapArray));

    // define the player emplacement
    mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;

    // declare Pokemons

    bulbizarre = new Pokemon(0);
    placePokemon(bulbizarre, MAP_PLAYER_X, MAP_PLAYER_Y + 2);

    carapuce = new Pokemon(true, 1);
    placePokemon(carapuce, MAP_PLAYER_X - 2, MAP_PLAYER_Y + 2);

    pokemon[0] = *bulbizarre;
    pokemon[1] = *carapuce;

    //________________________________________________________________________
}

/**
 * @brief Draw the map
 */
void Map::drawMap() {
    int cellType = 0;

    for (int row = 0; row < Map::MAP_HEIGHT; row++) {
        for (int column = 0; column < Map::MAP_WIDTH; column++) {
            cellType = first_level[row][column];
            destTexture.x = column * 32;
            destTexture.y = row * 32;

            // If the cell is a texture
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

            // If the cell is also the player emplacement
            if (mapArray[row][column] == MAP_PLAYER) {
                SDL_RenderCopy(Game::renderer, playerMapTexture, &srcPlayer, &destTexture);
            }

            // If the cell is also a pokemon emplacement
            // pokemonCounter-20 because the pokemonCounter start at 20 (to be according to MapTileFlag)
            // Maybe find a way to avoid the loop ?
            for (int i = 0; i < (pokemonCounter - 20); i++) {
                if (row == pokemon[i].getRow() && column == pokemon[i].getColumn()) {
                    srcPokemon.x = pokemon[i].getXSpriteCoordinate();
                    srcPokemon.y = pokemon[i].getYSpriteCoordinate();
                    SDL_RenderCopy(Game::renderer, pokemonMapTexture, &srcPokemon, &destTexture);
                }
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

    // On remet l'ancien emplacement du joueur à l'emplacement de la carte originale
    // On vérifie que le nouvel endroit où le joueur va marcher est bien une "walkable texture [1-10] dans MapTileFlag.hpp"
    int futurePlayerCellTexture = mapArray[MAP_PLAYER_Y + yOperator][MAP_PLAYER_X + xOperator];

    if (futurePlayerCellTexture >= 1 && futurePlayerCellTexture <= 10) {
        mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = first_level[MAP_PLAYER_Y][MAP_PLAYER_X];
        MAP_PLAYER_Y = MAP_PLAYER_Y + yOperator;
        MAP_PLAYER_X = MAP_PLAYER_X + xOperator;
        mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;
    }
}

/**
 * @brief Animate the player sprite
 */
void Map::updatePlayerSprite() {
    int speed = 100;
    int frames = 4;
    srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

/**
 * @brief Place the player sprite to the original position
 */
void Map::updatePlayerSpriteToDefault() {
    srcPlayer.x = 0;
}

/**
 * @brief Place a pokemon object on the map
 * @param pokemon, x, y
 */
void Map::placePokemon(Pokemon *pokemon, int x, int y) {
    mapArray[y][x] = pokemonCounter;
    pokemon->setCoordinates(x, y);
    pokemonCounter++;
}