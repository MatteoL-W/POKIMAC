#ifndef FLAG_GAME
#define FLAG_GAME
#include <iostream>

void initGame(SDL_Window* window, SDL_Renderer*& renderer);
void handleEvents();
void updateGame();
void renderGame(SDL_Renderer *renderer);
void cleanGame(SDL_Window *window, SDL_Renderer *renderer);

extern bool isGameRunning;

const std::string GAME_NAME = "POKIMAC";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;



#endif