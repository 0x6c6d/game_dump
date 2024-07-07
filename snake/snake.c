// gcc main.c -lSDL2 -o ../bin/snake

#include "snake.h"

void change_direction(snake_t *snake, direction_e dir) {
  direction_e cur_dir = (*snake).dir;

  if (cur_dir == dir)
    return;
  if (cur_dir == UP && dir == DOWN)
    return;
  if (cur_dir == DOWN && dir == UP)
    return;
  if (cur_dir == RIGHT && dir == LEFT)
    return;
  if (cur_dir == LEFT && dir == RIGHT)
    return;

  snake->dir = dir;
}

void move_snake(snake_t *snake) {
  switch ((*snake).dir) {
  case RIGHT:
    snake->rect.x += 1;
    break;
  case LEFT:
    snake->rect.x -= 1;
    break;
  case UP:
    snake->rect.y -= 1;
    break;
  case DOWN:
    snake->rect.y += 1;
    break;
  }
}

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow(
      "Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event e;

  // Setup snake
  snake_t snake;
  snake.dir = UP;
  snake.rect.h = SNAKE_BODY;
  snake.rect.w = SNAKE_BODY;
  snake.rect.x = WIN_W / 2;
  snake.rect.y = WIN_H / 2;

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
    move_snake(&snake);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &snake.rect);

    SDL_RenderPresent(renderer);
    SDL_Delay(25);
  }

  return 0;
}
