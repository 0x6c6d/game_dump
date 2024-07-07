// gcc main.c -lSDL2 -o ../bin/snake

#include "snake.h"
#include <ios>

void change_direction(snake_t *snake, direction_e dir){
  switch(dir){
    case RIGHT:
      snake->dir.right = true;
      snake->dir.left = false;
      snake->dir.up = false;
      snake->dir.down = false;
    case LEFT:
      snake->dir.right = false;
      snake->dir.left = true;
      snake->dir.up = false;
      snake->dir.down = false;
    case UP:
      snake->dir.right = false;
      snake->dir.left = false;
      snake->dir.up = true;
      snake->dir.down = false;
    case DOWN:
      snake->dir.right = false;
      snake->dir.left = false;
      snake->dir.up = false;
      snake->dir.down = true;
  }
};

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event e;

  snake_t snake;
  snake.dir.up = true;

  // Game Loop
  bool running = true;
  while (running) {

    // Check for user inputs
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
          change_direction(&snake, RIGHT);
        }
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          change_direction(&snake, LEFT);
        }
        switch (e.key.keysym.sym) {
        case SDLK_UP:
          change_direction(&snake, UP);
        }
        switch (e.key.keysym.sym) {
        case SDLK_DOWN:
          change_direction(&snake, DOWN);
        }
      }
    }

    // Move snake

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &snake);

    SDL_RenderPresent(renderer);
    SDL_Delay(25);
  }

  return 0;
}
