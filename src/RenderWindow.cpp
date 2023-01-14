#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *win_name, int w, int h)
    : window(nullptr), renderer(nullptr) {
  window = SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Log("Failed to initialise a window. Error: %s\n", SDL_GetError());
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_Log("Failed to initialise the renderer. Error: %s\n", SDL_GetError());
  }
}

SDL_Texture *RenderWindow::loadTexture(const char *filepath) {
  SDL_Texture *texture = NULL;
  texture = IMG_LoadTexture(renderer, filepath);

  if (!texture) {
    SDL_Log("Failed to load texture. Error: %s\n", SDL_GetError());
    return nullptr;
  }

  return texture;
}

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::render(SDL_Texture *tex) {
  SDL_RenderCopy(renderer, tex, NULL, NULL);
}

void RenderWindow::render(SDL_Texture *tex, SDL_Rect *clip,
                          SDL_Rect *renderQuad) {
  SDL_RenderCopy(renderer, tex, clip, renderQuad);
}

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::destroy() { SDL_DestroyWindow(window); }
