#ifndef FLAG_GAME
#define FLAG_GAME
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const std::string GAME_NAME = "POKIMAC";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initGame(SDL_Window* window, SDL_Renderer* renderer, bool *isGameRunning);
void handleEvents();
void updateGame();
void renderGame(SDL_Renderer *renderer);
void cleanGame(SDL_Window *window, SDL_Renderer *renderer);

#endif