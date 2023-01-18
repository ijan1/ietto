#ifndef SDL_WRAPPERS_HPP
#define SDL_WRAPPERS_HPP

#include <memory>

#include "SDL_assert.h"
#include "SDL_events.h"
#include "SDL_image.h"

struct SDL_TextureDestroyer {
  void operator()(SDL_Texture *p) { SDL_Log("Destroying SDL_Texture.\n");SDL_DestroyTexture(p); }
};
struct SDL_WindowDestroyer {
  void operator()(SDL_Window *p) { SDL_Log("Destoring SDL_Window.\n");SDL_DestroyWindow(p); }
};
struct SDL_RendererDestroyer {
  void operator()(SDL_Renderer *p) { SDL_Log("Destroying SDL_Renderer.\n");SDL_DestroyRenderer(p); }
};

using SDL_Texture_ptr = std::unique_ptr<SDL_Texture, SDL_TextureDestroyer>;
using SDL_Window_ptr = std::unique_ptr<SDL_Window, SDL_WindowDestroyer>;
using SDL_Renderer_ptr = std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer>;

inline void init_SDL() {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
  }

  int IMG_init_flags = IMG_INIT_PNG;
  if (IMG_Init(IMG_init_flags) != IMG_init_flags) {
    SDL_Log("Failed to initialise IMG_Init. Error: %s\n", SDL_GetError());
  }
}

#endif /* ifndef SDL_WRAPPERS_HPP */
