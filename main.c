#include <SDL2/SDL.h>
#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdio.h>

struct {
  SDL_Rect rect;
  SDL_Color bgColor;
  SDL_Color fgColor;
  const char *text;
} Button;
const int WIDTH = 1200;
const int HEIGHT = 800;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  SDL_Window *window =
      SDL_CreateWindow("Whatever", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  if (window == NULL) {
    SDL_Quit();
  }
  TTF_Font *font = TTF_OpenFont("./fonts/font.ttf", 10);
  if (font == NULL) {
    printf("Font is NULL\n");
    return 1;
  }
  // Create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
  SDL_RenderClear(renderer);
  // SDL_RenderDrawLine(renderer, 10, 10, 200, 200);
  // Rect init
  // Set the color of the rect SDL_SetRenderDrawColor(renderer, 255, 170, 120,
  // 255); SDL_RenderFillRect(renderer, rect); Draw the rect
  // SDL_RenderDrawRect(renderer, rect); Load font color
  SDL_Color color = {255, 255, 50, 255};
  SDL_Surface *textObject = TTF_RenderText_Solid(font, "Hello World", color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textObject);
  if (texture == NULL) {
    printf("SDL texture creation error: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Rect rect = {(WIDTH - 250) / 2, (HEIGHT - 250) / 2, 250, 250};
  SDL_FreeSurface(textObject);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_RenderPresent(renderer);
  SDL_Event event;

  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }

      switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == 98) {
          // char *clipboard = SDL_GetClipboardText();
          // printf(clipboard);
          // SDL_free(clipboard);
          int cpuCount = SDL_GetCPUCount();
          printf("Cpu count: %i\n", cpuCount);
          int memorySize = SDL_GetSystemRAM();
          printf("Memory Size: %i\n", memorySize);
          fflush(stdout);
          break;
        }
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_DestroyTexture(texture);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
