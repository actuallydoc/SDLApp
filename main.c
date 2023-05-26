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

// Step in pixels for moving the rectangles
const int STEP = 10;

int moveRectToDown(SDL_Rect *rect, SDL_Renderer *renderer,
                   SDL_Texture *texture) {
  if (rect->y < 0) {
    return 1;
  }
  SDL_RenderClear(renderer);
  rect->y = rect->y + STEP;
  SDL_RenderCopy(renderer, texture, NULL, rect);
  printf("New after changing Rect x is: %i\n", rect->x);
  SDL_RenderPresent(renderer);
  return 1;
}

int moveRectToUp(SDL_Rect *rect, SDL_Renderer *renderer, SDL_Texture *texture) {
  if (rect->y > 700 || rect->y < 0) {
    return 1;
  }
  SDL_RenderClear(renderer);
  rect->y = rect->y - STEP;
  SDL_RenderCopy(renderer, texture, NULL, rect);
  printf("New after changing Rect x is: %i\n", rect->x);
  SDL_RenderPresent(renderer);
  return 1;
}

int moveRectToLeft(SDL_Rect *rect, SDL_Renderer *renderer,
                   SDL_Texture *texture) {
  if (rect->x < 0 || rect->x > 950) {
    printf("Rect x is smaller than 0 and bigger than 950\n");
    return 0;
  }
  SDL_RenderClear(renderer);
  rect->x = rect->x - STEP;
  SDL_RenderCopy(renderer, texture, NULL, rect);
  printf("New after changing Rect x is: %i\n", rect->x);
  SDL_RenderPresent(renderer);
  return 1;
}
// This jjust renders the new rect tho?
int moveRectToRight(SDL_Rect *rect, SDL_Renderer *renderer,
                    SDL_Texture *texture) {

  if (rect->x < 0 || rect->x > 950) {
    return 0;
  }
  SDL_RenderClear(renderer);
  rect->x = rect->x + STEP;
  SDL_RenderCopy(renderer, texture, NULL, rect);
  printf("New after changing Rect x is: %i\n", rect->x);
  SDL_RenderPresent(renderer);
  return 1;
}

int changeTextColor(SDL_Rect rect, SDL_Renderer *renderer, SDL_Color color,
                    TTF_Font *font) {
  SDL_Surface *textObject = TTF_RenderText_Solid(font, "Hello World", color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textObject);
  if (texture == NULL) {
    printf("SDL texture creation error: %s\n", SDL_GetError());
    return 0;
  }
  SDL_FreeSurface(textObject);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_RenderPresent(renderer);
  return 1;
}
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
        printf("key: %i", event.key.keysym.sym);
        switch (event.key.keysym.sym) {
        case 100:
          // SDL_Color new_color = {10, 150, 20, 255};
          // if (changeTextColor(rect, renderer, new_color, font)) {
          //   printf("Success\n");
          // };
          if (moveRectToRight(&rect, renderer, texture)) {
            printf("Succecs moving it to right \n");
          }
          break;

        case 97:
          if (moveRectToLeft(&rect, renderer, texture)) {
            printf("Success moving it to left \n");
          };
          break;
        case 119:
          if (moveRectToUp(&rect, renderer, texture)) {
            printf("Success moving it up\n");
          }
          // char *clipboard = SDL_GetClipboardText();
          // printf(clipboard);
          // SDL_free(clipboard);
          // int cpuCount = SDL_GetCPUCount();
          // printf("Cpu count: %i\n", cpuCount);
          // int memorySize = SDL_GetSystemRAM();
          // printf("Memory Size: %i\n", memorySize);
          fflush(stdout);
          break;

        case 115:
          if (moveRectToDown(&rect, renderer, texture)) {
            printf("Success moving it down\n");
          }
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
