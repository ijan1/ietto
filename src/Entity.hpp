#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <utility>

#include "SDL_image.h"

class Entity {
 public:
  Entity();
  Entity(SDL_Texture *texture, SDL_Rect srcClip);

  const SDL_Texture *get_SDLTexture() const;
  const SDL_Rect *get_srcClip() const;
  int get_x_pos() const;
  int get_y_pos() const;
  int get_tile_size() const;

  void set_SDLTexture(const SDL_Texture *);
  void set_srcClip(SDL_Rect srcRect);
  void set_srcClip(int x, int y, int h, int w);
  void set_srcClip(int x, int y);
  void set_x_pos(int x);
  void set_y_pos(int y);
  void set_tile_size(int size);

  virtual void update() = 0;
 protected:
  std::pair<int, int> coordinates_; // x, y

  const SDL_Texture *texture_;
  SDL_Rect srcClip_;
  int tile_size_;
};

#endif /* ifndef ENTITY_HPP */
