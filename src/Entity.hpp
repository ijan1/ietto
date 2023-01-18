#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <utility>
#include <vector>

#include "SDL_image.h"
#include "SDL_log.h"

class Map;

class Entity {
 public:
  Entity(const SDL_Texture *texture, SDL_Rect srcClip);
  virtual ~Entity() = 0;

  const SDL_Texture *get_SDLTexture() const;
  const SDL_Rect *get_srcClip() const;
  std::pair<int, int> get_coordinates() const;
  int get_x() const;
  int get_y() const;
  int get_tile_size() const;

  void set_SDLTexture(const SDL_Texture *);
  void set_srcClip(SDL_Rect srcRect);
  void set_coordinates(std::pair<int, int> coordinates);
  void set_x(int x);
  void set_y(int y);
  void set_tile_size(int size);

  virtual void update(Map *map) = 0;

 private:
  std::pair<int, int> coordinates_;

  const SDL_Texture *texture_;
  SDL_Rect srcClip_;
  int tile_size_;
};

#endif /* ifndef ENTITY_HPP */
