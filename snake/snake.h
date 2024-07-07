#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

typedef enum { RIGHT, LEFT, UP, DOWN } direction_e;

typedef struct _direction {
  bool right;
  bool left;
  bool up;
  bool down;
} direction_t;

typedef struct _snake {
  direction_t dir;
  int x, y;
} snake_t;

void change_direction(snake_t *, direction_e);

#endif
