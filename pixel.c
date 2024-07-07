// gcc pixel.c -lSDL2 -o bin/pixel

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

int main() {
  bool running = true;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Event e;
  SDL_Rect r = {10, 10, 10, 10};

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }

  return 0;
}
