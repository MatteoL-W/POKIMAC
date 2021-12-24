#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/MapsArray.hpp"
#include "../include/Pokemon.hpp"

Pokemon *bulbizarre = nullptr;
Pokemon *carapuce = nullptr;
int pokemonCounter = 20;

/**
 * @brief Constructor of the Map object
 */
Map::Map(bool isCameraCentered) {
    tilesetMapTexture = IMG_LoadTexture(Game::renderer, "assets/tileset_map_texture.png");
    playerMapTexture = IMG_LoadTexture(Game::renderer, "assets/ethan_sprite.png");
    pokemonMapTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");

    srcTexture.x = srcTexture.y = 0;
    srcTexture.w = srcTexture.h = 32;
    srcPlayer.h = srcPlayer.w = 64;
    srcPokemon = srcTexture;

    if (isCameraCentered) {
        MAP_CELL_WIDTH = 32 * 5;
        MAP_CELL_HEIGHT = 32 * 5;
    }

    destTexture.w = MAP_CELL_WIDTH;
    destTexture.h = MAP_CELL_HEIGHT;
    destTexture.x = destTexture.y = 0;

    centeredCamera = isCameraCentered;

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

    carapuce = new Pokemon(1);
    placePokemon(carapuce, MAP_PLAYER_X + 3, MAP_PLAYER_Y + 1);

    pokemon[0] = *bulbizarre;
    pokemon[1] = *carapuce;

    //________________________________________________________________________
}

/**
 * @brief Draw the map
 */
void Map::drawMap() {
    int cellType = 0, startingY = 0, startingX = 0;
    int endingY = Map::MAP_HEIGHT;
    int endingX = Map::MAP_WIDTH;

    if (centeredCamera) {
        // X viewport with padding
        startingX = getStartingPos(MAP_PLAYER_X, Map::MAP_WIDTH, 2);
        endingX = getEndingPos(MAP_PLAYER_X, Map::MAP_WIDTH, 2);

        // Y viewport with padding
        startingY = getStartingPos(MAP_PLAYER_Y, Map::MAP_HEIGHT, 2);
        endingY = getEndingPos(MAP_PLAYER_Y, Map::MAP_HEIGHT, 2);
    }

    for (int row = startingY; row <= endingY; row++) {
        for (int column = startingX; column <= endingX; column++) {
            cellType = first_level[row][column];

            // The 1st rendered cell start at 0 on the top left screen (except if a padding is added)
            destTexture.x = (-startingX + column) * MAP_CELL_WIDTH;
            destTexture.y = (-startingY + row) * MAP_CELL_HEIGHT;

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
            for (int i = 0; i < (pokemonCounter - 20); i++) {
                if (row == pokemon[i].getRow() && column == pokemon[i].getColumn()) {
                    if ((row - 1 == MAP_PLAYER_Y && column == MAP_PLAYER_X) ||
                        (row + 1 == MAP_PLAYER_Y && column == MAP_PLAYER_X) ||
                        (column - 1 == MAP_PLAYER_X && row == MAP_PLAYER_Y) ||
                        (column + 1 == MAP_PLAYER_X && row == MAP_PLAYER_Y)) {
                        std::cout << "interactions";
                    }

                    srcPokemon.x = pokemon[i].getXSpriteCoordinate();
                    srcPokemon.y = pokemon[i].getYSpriteCoordinate();
                    SDL_RenderCopy(Game::renderer, pokemonMapTexture, &srcPokemon, &destTexture);
                }
            }
        }
    }
}

/**
 * @brief Toggle the camera between debug and centered
 */
void Map::toggleCamera() {
    if (centeredCamera) {
        centeredCamera = false;
        MAP_CELL_WIDTH = 32;
        MAP_CELL_HEIGHT = 32;
    } else {
        centeredCamera = true;
        MAP_CELL_WIDTH = 32 * 5;
        MAP_CELL_HEIGHT = 32 * 5;
    }
    destTexture.w = MAP_CELL_WIDTH;
    destTexture.h = MAP_CELL_HEIGHT;
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

int getStartingPos(int playerPosition, int mapWidth, int centeredScale) {
    int startingViewport = (playerPosition - centeredScale < 0) ? 0 : playerPosition - centeredScale;
    int padding = (playerPosition + centeredScale > mapWidth - 1) ? (playerPosition + centeredScale - (mapWidth - 1))
                                                                  : 0;
    return startingViewport - padding;
}

int getEndingPos(int playerPosition, int mapWidth, int centeredScale) {
    int endingViewport = (playerPosition + 2 >= mapWidth - 1) ? mapWidth - 1 : playerPosition + 2;
    int padding = (playerPosition - 2 < 0) ? abs(mapWidth - 2) : 0;
    return endingViewport + padding;
}
