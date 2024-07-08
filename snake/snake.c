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

void move_snake(snake_t *snake, int speed) {
  switch ((*snake).dir) {
  case RIGHT:
    snake->rect.x += speed;
    if (snake->rect.x == WIN_W) {
      snake->rect.x = 0;
    }
    break;
  case LEFT:
    snake->rect.x -= speed;
    if (snake->rect.x == 0) {
      snake->rect.x = WIN_W;
    }
    break;
  case UP:
    snake->rect.y -= speed;
    if (snake->rect.y == 0) {
      snake->rect.y = WIN_H;
    }
    break;
  case DOWN:
    snake->rect.y += speed;
    if (snake->rect.y == WIN_H) {
      snake->rect.y = 0;
    }
    break;
  }
}

SDL_Rect create_apple() {
  int x = REC_SIZE + rand() % (WIN_W - REC_SIZE - REC_SIZE + 1);
  int y = REC_SIZE + rand() % (WIN_H - REC_SIZE - REC_SIZE);
  SDL_Rect apple = {x, y, REC_SIZE, REC_SIZE};
  return apple;
}

int main() {
  srand(time(NULL));

  // Setup variables
  int speed = START_SPEED;
  bool game_running = true;
  bool new_apple = false;

  // Setup snake + apple
  SDL_Rect apple = create_apple();
  snake_t snake = {UP, {WIN_W / 2, WIN_H / 2, REC_SIZE, REC_SIZE}};

  // Setup SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow(
      "Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event e;

  // Game Loop
  while (game_running) {
    // Check for user inputs
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        game_running = false;
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

    // Create apple
    if (new_apple) {
      apple = create_apple();
    }

    // Move snake
    move_snake(&snake, speed);

    // Render map
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render apple
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &apple);

    // Render snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &snake.rect);

    // Render scene
    SDL_RenderPresent(renderer);
    SDL_Delay(25);
  }

  return 0;
}
