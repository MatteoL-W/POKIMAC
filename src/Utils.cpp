#include <iostream>
#include <random>
#include "../include/Utils.hpp"

/**
 * @brief Get the left padding to center the text according to the block
 * @param blockWidth
 * @param textWidth
 * @return
 */
int getPadding(int blockWidth, int textWidth) {
    return (blockWidth - textWidth) / 2;
}

/**
 * @brief Get the starting cell of the camera according to the map size
 * @param playerPosition
 * @param mapWidth
 * @param centeredScale
 * @return
 */
int getStartingPos(int playerPosition, int mapWidth, int centeredScale) {
    int startingViewport = (playerPosition - centeredScale < 0) ? 0 : playerPosition - centeredScale;
    int padding = (playerPosition + centeredScale > mapWidth - 1) ? (playerPosition + centeredScale - (mapWidth - 1))
                                                                  : 0;
    return startingViewport - padding;
}

/**
 * @brief Get the ending cell of the camera according to the map size
 * @param playerPosition
 * @param mapWidth
 * @param centeredScale
 * @return
 */
int getEndingPos(int playerPosition, int mapWidth, int centeredScale) {
    int endingViewport = (playerPosition + 2 >= mapWidth - 1) ? mapWidth - 1 : playerPosition + 2;
    int padding = (playerPosition - 2 < 0) ? abs(mapWidth - 2) : 0;
    return endingViewport + padding;
}

/**
 * @brief Get a random number from 0 - max
 * @param max
 * @return
 */
int getRandomNumberTo(int max) {
    std::random_device rd;
    return rand() % max;
}