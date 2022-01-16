#pragma once

// *****************************************************
// Non-walkable texture [0]
const int MAP_WATER = 0;

// Walkable textures [1-18]
const int MAP_GRASS = 1;
const int MAP_DIRT = 2;

// Walkable textures but pokemons not allowed to spawn on
const int MAP_GRASS_NO_POKEMON = 11;
const int MAP_DIRT_NO_POKEMON = 12;

// Non-walkable texture [14-17]
const int MAP_GRASS_NOT_WALKABLE = 14;
const int MAP_DIRT_NOT_WALKABLE = 15;

// *****************************************************
// Player [19]
const int MAP_PLAYER = 19;

// *****************************************************
// Pokemon [20 - 70]
// Dynamic value

// *****************************************************
// Decors [70 - ??]
const int MAP_HEALTH_CENTER = 71;

// *****************************************************
// Direction [100 - 103]
const int MOVE_RIGHT = 100;
const int MOVE_LEFT = 101;
const int MOVE_DOWN = 102;
const int MOVE_UP = 103;