#ifndef FLAG_GAME
#define FLAG_GAME

void initGame(SDL_Window* window, SDL_Renderer* renderer, bool *isGameRunning);
void handleEvents(bool *isGameRunning);
void updateGame();
void renderGame(SDL_Renderer *renderer);
void cleanGame(SDL_Window *window, SDL_Renderer *renderer);

#endif