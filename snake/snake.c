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
  switch ((*snake).dir) {
  case RIGHT:
    snake->rect.x += REC_SIZE;
    if (snake->rect.x == WIN_W) {
      snake->rect.x = 0;
    }
    break;
  case LEFT:
    snake->rect.x -= REC_SIZE;
    if (snake->rect.x == 0) {
      snake->rect.x = WIN_W;
    }
    break;
  case UP:
    snake->rect.y -= REC_SIZE;
    if (snake->rect.y == 0) {
      snake->rect.y = WIN_H;
    }
    break;
  case DOWN:
    snake->rect.y += REC_SIZE;
    if (snake->rect.y == WIN_H) {
      snake->rect.y = 0;
    }
    break;
  }
}

SDL_Rect create_apple() {
  int x = rand() % (WIN_W - REC_SIZE + 1); // 0 - 630
  int x_base10 = x - (x % REC_SIZE);       // only hit 0, 10, 20 etc.
  int y = rand() % (WIN_H - REC_SIZE + 1); // 0 - 470
  int y_base10 = y - (y % REC_SIZE);
  SDL_Rect apple = {x_base10, y_base10, REC_SIZE, REC_SIZE};
  return apple;
}

bool detect_collision(snake_t *snake, SDL_Rect *apple) {
  if (snake->rect.x == apple->x && snake->rect.y == apple->y) {
    return true;
  }

  return false;
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
  int score = 0;
  bool game_running = true;

  // Setup snake + apple
  SDL_Rect apple = create_apple();
  snake_t snake = {UP, {WIN_W / 2, WIN_H / 2, REC_SIZE, REC_SIZE}};

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
    fprintf(stderr, "error: font not found -> change it inside the snake.h file\n");
    return 1;
  }

  // Game Loop
  while (game_running) {
    // Check for user inputs
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        game_running = false;
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

    // Move snake
    move_snake(&snake);

    // Detect collision
    bool collision = detect_collision(&snake, &apple);

    // Create new apple
    if (collision) {
      apple = create_apple();
      collision = false;
    }

    // Render map
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render apple
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &apple);

    // Render snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &snake.rect);

    // Render score
    render_text(renderer, 5, 5, "Score:", font, &score_rect, &color);

    // Render scene
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
