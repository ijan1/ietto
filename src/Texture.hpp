#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SDL_image.h"

class Texture {
  public:
    Texture(SDL_Texture *, SDL_Rect *clip);
  private:
    SDL_Texture *texture_;
    SDL_Rect srcClip_;
}

#endif /* ifndef TEXTURE_HPP */
