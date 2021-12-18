#pragma once

#include "MapTileFlag.hpp"

class Map {
public:
    static const int MAP_HEIGHT = 20;
    static const int MAP_WIDTH = 25;
    int MAP_PLAYER_Y = 3;
    int MAP_PLAYER_X = 8;

    Map();

    ~Map();

    void loadMap(int array[MAP_HEIGHT][MAP_WIDTH]);

    void drawMap();

    void updatePlayerPosition(int direction);

    void updatePlayerSprite();

    void updatePlayerSpriteToDefault();

private:
    SDL_Rect src, dest, srcPlayer, destPlayer;
    SDL_Texture* tilesetMapTexture;
    SDL_Texture* playerMapTexture;
    int mapArray[MAP_HEIGHT][MAP_WIDTH];
};