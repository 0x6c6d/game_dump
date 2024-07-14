// gcc snake.c -lSDL2 -lSDL2_ttf -o ../bin/snake

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
  // shift every rect one index up & place last rect at the start
  SDL_Rect temp_first = snake->rects[0];
  SDL_Rect temp_last = snake->rects[snake->rects_size - 1];
  for (int i = snake->rects_size - 1; i > 0; --i) {
    snake->rects[i] = snake->rects[i - 1];
  }
  snake->rects[0] = temp_first;

  switch ((*snake).dir) {
  case RIGHT:
    snake->rects[0].x = temp_first.x + REC_SIZE;
    if (snake->rects[0].x == WIN_W) {
      snake->rects[0].x = 0;
    }
    break;
  case LEFT:
    snake->rects[0].x = temp_first.x - REC_SIZE;
    if (snake->rects[0].x == -REC_SIZE) {
      snake->rects[0].x = WIN_W - REC_SIZE;
    }
    break;
  case UP:
    snake->rects[0].y = temp_first.y - REC_SIZE;
    if (snake->rects[0].y == -REC_SIZE) {
      snake->rects[0].y = WIN_H - REC_SIZE;
    }
    break;
  case DOWN:
    snake->rects[0].y = temp_first.y + REC_SIZE;
    if (snake->rects[0].y == WIN_H) {
      snake->rects[0].y = 0;
    }
    break;
  }
}

SDL_Rect create_apple() {
  int x = REC_SIZE + rand() % (WIN_W - 3 * REC_SIZE + 1); // 20 - 600
  int x_base10 = x - (x % REC_SIZE); // only hit 0, 10, 20 etc.

  int y = 2 * REC_SIZE + rand() % (WIN_H - 3 * REC_SIZE + 1); // 40 - 460
  int y_base10 = y - (y % REC_SIZE);

  SDL_Rect apple = {x_base10, y_base10, REC_SIZE, REC_SIZE};
  return apple;
}

bool detect_collision_apple(snake_t *snake, SDL_Rect *apple) {
  if (snake->rects[0].x == apple->x && snake->rects[0].y == apple->y) {
    return true;
  }

  return false;
}

bool detect_collision_snake(snake_t *snake) {
  for (int i = 1; i < snake->rects_size - 1; ++i) {
    if (snake->rects[0].x == snake->rects[i].x &&
        snake->rects[0].y == snake->rects[i].y) {
      return true;
    }
  }
  return false;
}

void create_new_snake_rect(snake_t *snake) {
  int rect_size = snake->rects_size;
  if (snake->rects_size >= MAX_SCORE) {
    return;
  }

  SDL_Rect new_head = snake->rects[rect_size - 1];
  switch ((*snake).dir) {
  case UP:
    new_head.y += 2 * REC_SIZE;
  case DOWN:
    new_head.y -= REC_SIZE;
    new_head.x += REC_SIZE;
  case RIGHT:
    new_head.x -= 2 * REC_SIZE;
  case LEFT:
    new_head.x += REC_SIZE;
  }

  snake->rects[rect_size] = new_head;
  snake->rects_size += 1;
}

void render_text(SDL_Renderer *renderer, int x, int y, const char *text,
                 TTF_Font *font, SDL_Rect *rect, SDL_Color *color) {
  SDL_Surface *surface;
  SDL_Texture *texture;

  surface = TTF_RenderText_Solid(font, text, *color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  rect->x = x;
  rect->y = y;
  rect->w = surface->w;
  rect->h = surface->h;

  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, rect);
  SDL_DestroyTexture(texture);
}

int main() {
  // Setup stuff
  srand(time(NULL));
  int snake_speed = 1;
  int score = 0;
  char *score_str;
  bool game_over = false;
  bool gameloop_running = true;

  // Setup snake + apple
  SDL_Rect apple = create_apple();
  SDL_Rect head = {WIN_W / 2, WIN_H / 2, REC_SIZE, REC_SIZE};
  snake_t snake;
  snake.dir = UP;
  snake.rects[0] = head;
  snake.rects_size = 1;

  // Setup SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow(
      "Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event e;

  // Setup text (for game score)
  SDL_Rect score_rect;
  SDL_Color color = {233, 233, 233, 255};
  TTF_Init();
  TTF_Font *font = TTF_OpenFont(CUSTOM_FONT, 24);
  if (font == NULL) {
    fprintf(stderr,
            "error: font not found -> change it inside the snake.h file\nerror "
            "msg: %s\n",
            TTF_GetError());
    return 1;
  }

  // Game Loop
  while (gameloop_running) {
    // Check for user inputs
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        gameloop_running = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
        case SDLK_l:
        case SDLK_d:
          change_direction(&snake, RIGHT);
          break;
        case SDLK_LEFT:
        case SDLK_h:
        case SDLK_a:
          change_direction(&snake, LEFT);
          break;
        case SDLK_UP:
        case SDLK_k:
        case SDLK_w:
          change_direction(&snake, UP);
          break;
        case SDLK_DOWN:
        case SDLK_j:
        case SDLK_s:
          change_direction(&snake, DOWN);
          break;
        default:
          break;
        }
      }
    }

    if (game_over) {
      SDL_Delay(100);
      continue;
    }

    // Render map
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Move snake
    move_snake(&snake);

    // Detect collision
    bool collision_snake = detect_collision_snake(&snake);
    if (collision_snake) {
      game_over = true;
      asprintf(&score_str, "Game over! Score: %d", score);
      render_text(renderer, 5, 5, score_str, font, &score_rect, &color);
      SDL_RenderPresent(renderer);
      continue;
    }

    bool collision_apple = detect_collision_apple(&snake, &apple);

    // Create new apple
    if (collision_apple) {
      collision_apple = false;
      score += 1;

      if (score == MAX_SCORE) {
        game_over = true;
        asprintf(&score_str, "You won! Score: %d", score);
        render_text(renderer, 5, 5, score_str, font, &score_rect, &color);
        SDL_RenderPresent(renderer);
        continue;
      }

      if (snake_speed < 15)
        snake_speed += 1;

      create_new_snake_rect(&snake);
      apple = create_apple();
    }

    // Render score
    asprintf(&score_str, "Score: %d", score);
    render_text(renderer, 5, 5, score_str, font, &score_rect, &color);

    // Render apple
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &apple);

    // Render snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < snake.rects_size; ++i) {
      SDL_RenderFillRect(renderer, &snake.rects[i]);
    }

    // Render scene
    SDL_RenderPresent(renderer);

    int delay =
        200 -
        (10 * (snake_speed - 1)); // sp 1 = 200, sp 2 = 190, sp 3 = 180 ...
    SDL_Delay(delay);
  }

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
