#ifndef SDL_WRAPPERS_HPP
#define SDL_WRAPPERS_HPP

#include <memory>

#include "SDL_assert.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_log.h"

namespace SDL {

struct TextureDestroyer {
  void operator()(SDL_Texture *p) { SDL_DestroyTexture(p); }
};
struct WindowDestroyer {
  void operator()(SDL_Window *p) { SDL_DestroyWindow(p); }
};
struct RendererDestroyer {
  void operator()(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
};

using Texture_ptr = std::unique_ptr<SDL_Texture, TextureDestroyer>;
using Window_ptr = std::unique_ptr<SDL_Window, WindowDestroyer>;
using Renderer_ptr = std::unique_ptr<SDL_Renderer, RendererDestroyer>;

inline void init() {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
  }

  int IMG_init_flags = IMG_INIT_PNG;
  if (IMG_Init(IMG_init_flags) != IMG_init_flags) {
    SDL_Log("Failed to initialise IMG_Init. Error: %s\n", SDL_GetError());
  }
}


} // namespace SDL
#endif /* ifndef SDL_WRAPPERS_HPP */
