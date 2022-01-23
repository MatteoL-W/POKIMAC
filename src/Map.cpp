#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/MapsArray.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Utils.hpp"

Pokemon *newPokemon = nullptr;

int startingI = 0;
int *health_center_coordinates = nullptr;
int pokemonCounter = 20;
// 20 because dynamic value (cf. MapTileFlag.hpp)

/**
 * @brief Constructor of the Map object
 */
Map::Map(bool isCameraCentered) {
    tilesetMapTexture = IMG_LoadTexture(Game::renderer, "assets/all2_tileset_map_texture.png");
    HealthCenterMapTexture = IMG_LoadTexture(Game::renderer, "assets/tileset1.png");

    defineSrcRectsValues();

    if (isCameraCentered) {
        MAP_CELL_WIDTH = Game::SCALE_CAMERA * 32 * 5;
        MAP_CELL_HEIGHT = Game::SCALE_CAMERA * 32 * 5;
    }

    defineDestRectsValues();

    centeredCamera = isCameraCentered;

    Map::loadMap(allMaps[Game::level]);
}

Map::~Map() {

}

/**
 * @brief Define the values of the SDL_Rect (src) objects
 */
void Map::defineSrcRectsValues() {
    srcTexture.x = srcTexture.y = 0;
    srcTexture.w = srcTexture.h = 32;

    srcPlayer.x = srcPlayer.y = 0;
    srcPlayer.h = srcPlayer.w = 64;

    srcPokemon = srcTexture;

    srcHealthCenter.x = 0;
    srcHealthCenter.y = 240;
    srcHealthCenter.w = srcHealthCenter.h = 80;
}

/**
 * @brief Define the values of the SDL_Rect (dest) objects
 */
void Map::defineDestRectsValues() {
    dest1by1.w = MAP_CELL_WIDTH;
    dest1by1.h = MAP_CELL_HEIGHT;
    dest1by1.x = dest1by1.y = 0;

    dest2by2.w = MAP_CELL_WIDTH * 2;
    dest2by2.h = MAP_CELL_HEIGHT * 2;
    dest2by2.x = dest2by2.y = 0;
}

/**
 * @Brief Copy the external map into our map system
 * @param array
 */
void Map::loadMap(const int array[Map::MAP_HEIGHT][Map::MAP_WIDTH]) {
    // Copy of mapArray from level's map
    SDL_memmove(mapArray, array, sizeof(mapArray));

    switch (Game::level) {
        case BOSS_LEVEL:
            MAP_PLAYER_Y = 22;
            MAP_PLAYER_X = 12;
            break;

        case 1:
            MAP_PLAYER_Y = 4;
            MAP_PLAYER_X = 9;
            break;

        case 2:
            MAP_PLAYER_Y = 2;
            MAP_PLAYER_X = 19;
            break;

        case 3:
            MAP_PLAYER_Y = 23;
            MAP_PLAYER_X = 20;
            break;

        case 4:
            MAP_PLAYER_Y = 1;
            MAP_PLAYER_X = 1;
            break;
    }

    // define the player emplacement
    mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = MAP_PLAYER;

    loadPokemons();
}

/**
 * @brief Load the Pokemons
 */
void Map::loadPokemons() {
    startingI = Game::level * 6;

    // Spawn MewTwo at last level
    if (Game::level == BOSS_LEVEL) {
        Pokemon *mewTwo = new Pokemon(POKEMON_MEWTWO);
        placePokemon(mewTwo, 12, 2);
        pokemon[startingI + 1] = *mewTwo;
        return;
    }

    // Place pokemons randomly and make them spawn on the walkable textures
    for (int i = startingI; i < startingI + 6; i++) {
        newPokemon = new Pokemon(pokemonsFromMaps[Game::level][i - startingI]);
        int randomX = getRandomNumberTo(MAP_WIDTH);
        int randomY = getRandomNumberTo(MAP_HEIGHT);

        // Make pokemon spawn on water if level == 1
        int startingTexture = (Game::level == 1) ? 14 : 1;
        int endingTexture = (Game::level == 1) ? 14 : 10;

        while (mapArray[randomY][randomX] < startingTexture || mapArray[randomY][randomX] > endingTexture) {
            randomX = getRandomNumberTo(MAP_WIDTH);
            randomY = getRandomNumberTo(MAP_HEIGHT);
        }

        int generatedCoordinates[2] = {
                randomX,
                randomY
        };

        placePokemon(newPokemon, generatedCoordinates[0], generatedCoordinates[1]);
        pokemon[i] = *newPokemon;
    }
}

void Map::draw() {
    startingY = 0, startingX = 0;
    endingY = Map::MAP_HEIGHT;
    endingX = Map::MAP_WIDTH;

    if (centeredCamera) {
        // X viewport with padding
        startingX = getStartingPos(MAP_PLAYER_X, Map::MAP_WIDTH, 2);
        endingX = getEndingPos(MAP_PLAYER_X, Map::MAP_WIDTH, 2);

        // Y viewport with padding
        startingY = getStartingPos(MAP_PLAYER_Y, Map::MAP_HEIGHT, 2);
        endingY = getEndingPos(MAP_PLAYER_Y, Map::MAP_HEIGHT, 2);
    }

    drawMap();
    drawExtras();
}

/**
 * @brief Draw the map
 */
void Map::drawMap() {
    int cellType = 0;
    for (int row = startingY; row <= endingY; row++) {
        for (int column = startingX; column <= endingX; column++) {
            cellType = allMaps[Game::level][row][column];

            // The 1st rendered cell start at 0 on the top left screen (except if a padding is added)
            dest1by1.x = (-startingX + column) * MAP_CELL_WIDTH;
            dest1by1.y = (-startingY + row) * MAP_CELL_HEIGHT;

            //If the cell is a texture
            switch (cellType) {
                case MAP_WATER:
                    srcTexture.x = 64;
                    srcTexture.y = Game::level * 32;
                    break;
                case MAP_GRASS:
                case MAP_GRASS_NO_POKEMON:
                case MAP_GRASS_NOT_WALKABLE:
                    srcTexture.x = 32;
                    srcTexture.y = Game::level * 32;
                    break;
                case MAP_DIRT:
                case MAP_DIRT_NO_POKEMON:
                case MAP_DIRT_NOT_WALKABLE:
                    srcTexture.x = 0;
                    srcTexture.y = Game::level * 32;
                    break;
                default:
                    break;
            }

            SDL_RenderCopy(Game::renderer, tilesetMapTexture, &srcTexture, &dest1by1);

            // If the cell is also the player emplacement
            if (mapArray[row][column] == MAP_PLAYER) {
                SDL_RenderCopy(Game::renderer, Game::characterTexture, &srcPlayer, &dest1by1);
            }
        }
    }
}

/**
 * @brief Draw decors and pokemons
 */
void Map::drawExtras() {
    Map::canAttack = nullptr;
    // Each map draw 6 pokemons
    startingI = Game::level * 6;

    // Draw MewTwo
    if (Game::level == BOSS_LEVEL) {
        drawPokemon(startingI + 1);
        return;
    }

    // Drawing all the pokemons
    for (int i = startingI; i < startingI + 6; i++) {
        drawPokemon(i);
    }

    health_center_coordinates = findTiles(allMaps[Game::level], MAP_HEALTH_CENTER);
    if (health_center_coordinates != nullptr) {
        drawHealthCenter();
    }
}

/**
 * @brief Draw pokemon in the screen + get the interactivity
 * @param i
 */
void Map::drawPokemon(int i) {
    int row = pokemon[i].getRow();
    int column = pokemon[i].getColumn();

    dest1by1.x = (-startingX + column) * MAP_CELL_WIDTH;
    dest1by1.y = (-startingY + row) * MAP_CELL_HEIGHT;

    if ((row - 1 == MAP_PLAYER_Y && column == MAP_PLAYER_X) ||
        (row + 1 == MAP_PLAYER_Y && column == MAP_PLAYER_X) ||
        (column - 1 == MAP_PLAYER_X && row == MAP_PLAYER_Y) ||
        (column + 1 == MAP_PLAYER_X && row == MAP_PLAYER_Y)) {
        Map::canAttack = &(pokemon[i]);
    }

    srcPokemon.x = pokemon[i].getXSpriteCoordinate();
    srcPokemon.y = pokemon[i].getYSpriteCoordinate();
    SDL_RenderCopy(Game::renderer, Game::pokemonsTexture, &srcPokemon, &dest1by1);
}

/**
 * @brief Toggle the camera between debug and centered
 */
void Map::toggleCamera() {
    if (centeredCamera) {
        centeredCamera = false;
        MAP_CELL_WIDTH = MAP_CELL_HEIGHT = 32 * Game::SCALE_CAMERA;
    } else {
        centeredCamera = true;
        MAP_CELL_WIDTH = MAP_CELL_HEIGHT = 32 * Game::SCALE_CAMERA * 5;
    }

    dest1by1.w = MAP_CELL_WIDTH;
    dest1by1.h = MAP_CELL_HEIGHT;
    dest2by2.w = MAP_CELL_WIDTH * 2;
    dest2by2.h = MAP_CELL_HEIGHT * 2;
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

    if (futurePlayerCellTexture >= 1 && futurePlayerCellTexture <= 13) {
        mapArray[MAP_PLAYER_Y][MAP_PLAYER_X] = allMaps[Game::level][MAP_PLAYER_Y][MAP_PLAYER_X];
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

/**
 * @brief Find a tile from a level with his map code (cf. MapTileFlag.hpp)
 * @param level
 * @param map_nb
 * @return
 */
int *Map::findTiles(const int level[Map::MAP_HEIGHT][Map::MAP_WIDTH], int map_nb) {
    static int coordinates[2];
    for (int row = 0; row <= Map::MAP_WIDTH; row++) {
        for (int column = 0; column <= Map::MAP_HEIGHT; column++) {
            if (level[row][column] == map_nb) {
                coordinates[0] = column;
                coordinates[1] = row;
                return coordinates;
            }
        }
    }
    return nullptr;
}

/**
 * @brief Draw the Health Center
 */
void Map::drawHealthCenter() {
    Map::canBeCured = false;

    int column = health_center_coordinates[0];
    int row = health_center_coordinates[1];

    dest2by2.x = (-startingX + column) * MAP_CELL_WIDTH;
    dest2by2.y = (-startingY + row) * MAP_CELL_HEIGHT;
    SDL_RenderCopy(Game::renderer, HealthCenterMapTexture, &srcHealthCenter, &dest2by2);

    // If the player is around the health center
    if ((row - 1 == MAP_PLAYER_Y && column - 1 == MAP_PLAYER_X) ||
        (row == MAP_PLAYER_Y && column - 1 == MAP_PLAYER_X) ||
        (row + 1 == MAP_PLAYER_Y && column - 1 == MAP_PLAYER_X) ||
        (row + 2 == MAP_PLAYER_Y && column - 1 == MAP_PLAYER_X) ||
        (row + 2 == MAP_PLAYER_Y && column == MAP_PLAYER_X) ||
        (row + 2 == MAP_PLAYER_Y && column + 1 == MAP_PLAYER_X) ||
        (row + 2 == MAP_PLAYER_Y && column + 2 == MAP_PLAYER_X) ||
        (row + 1 == MAP_PLAYER_Y && column + 2 == MAP_PLAYER_X) ||
        (row == MAP_PLAYER_Y && column + 2 == MAP_PLAYER_X) ||
        (row - 1 == MAP_PLAYER_Y && column + 2 == MAP_PLAYER_X) ||
        (row - 1 == MAP_PLAYER_Y && column + 1 == MAP_PLAYER_X) ||
        (row - 1 == MAP_PLAYER_Y && column == MAP_PLAYER_X)
            ) {
        Map::canBeCured = true;
    }
}
