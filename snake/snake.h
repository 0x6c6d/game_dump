#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define WIN_H 480
#define WIN_W 640
#define SNAKE_BODY 10

typedef enum { RIGHT, LEFT, UP, DOWN } direction_e;

typedef struct _snake {
  SDL_Rect rect;
  direction_e dir;
} snake_t;

void change_direction(snake_t *, direction_e);
void move_snake(snake_t *);

#endif
