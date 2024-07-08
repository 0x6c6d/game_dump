#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <time.h>

#define WIN_H 480
#define WIN_W 640
#define REC_SIZE 10
#define START_SPEED 2

typedef enum { RIGHT, LEFT, UP, DOWN } direction_e;

typedef struct _snake {
  direction_e dir;
  SDL_Rect rect;
} snake_t;

void change_direction(snake_t *, direction_e);
void move_snake(snake_t *, int);
SDL_Rect create_apple();

#endif
