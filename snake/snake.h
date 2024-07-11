#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <time.h>

#define WIN_H 480
#define WIN_W 640
#define REC_SIZE 20
#define MAX_SCORE 50
// installed font via: sudo pacman -S gnu-free-fonts
#define CUSTOM_FONT "/usr/share/fonts/gnu-free/FreeMono.otf"

typedef enum { RIGHT, LEFT, UP, DOWN } direction_e;

typedef struct _snake {
  direction_e dir;
  SDL_Rect rect;
} snake_t;

void change_direction(snake_t *, direction_e);
void move_snake(snake_t *);
SDL_Rect create_apple();
bool detect_collision(snake_t *, SDL_Rect *);
void render_text(SDL_Renderer *renderer, int x, int y, const char *text,
                 TTF_Font *font, SDL_Rect *rect, SDL_Color *color);

#endif
