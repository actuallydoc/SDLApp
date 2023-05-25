#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdio.h>

struct {
  SDL_Rect rect;
  SDL_Color bgColor;
  SDL_Color fgColor;
  const char *text;
} Button;

int main(int argc, char *argv[]) {

  int WIDTH = 800;
  int HEIGHT = 800;
  // Make a SDL Window
  SDL_Window *window =
      SDL_CreateWindow("Whatever", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  if (window == NULL) {
    SDL_Quit();
  }

  // Create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
  SDL_RenderDrawLine(renderer, 10, 10, 200, 200);
  SDL_RenderPresent(renderer);
  SDL_Event event;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
