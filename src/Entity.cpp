#include "Entity.hpp"

Entity::Entity(const SDL_Texture *texture, SDL_Rect srcClip)
    : coordinates_(1, 1),
      texture_(texture), // NOTE: Assuming that h = w
      srcClip_(srcClip),
      tile_size_(srcClip.h) {}

Entity::~Entity() {}

const SDL_Texture *Entity::get_SDLTexture() const { return texture_; }
const SDL_Rect *Entity::get_srcClip() const { return &srcClip_; }
std::pair<int, int> Entity::get_coordinates() const { return coordinates_; };
int Entity::get_x() const { return coordinates_.first; }
int Entity::get_y() const { return coordinates_.second; }
int Entity::get_tile_size() const { return tile_size_; }

void Entity::set_SDLTexture(const SDL_Texture *texture) { texture_ = texture; }
void Entity::set_srcClip(SDL_Rect srcClip) {
  srcClip_.x = srcClip.x;
  srcClip_.y = srcClip.y;
  srcClip_.h = srcClip.h;
  srcClip_.w = srcClip.w;
}
void Entity::set_srcClip(int x, int y, int h, int w) {
  srcClip_.x = x;
  srcClip_.y = y;
  srcClip_.h = h;
  srcClip_.w = w;
}
// TODO: fix the coordinate system
// void Entity::set_coordinates(std::pair<int, int> coordinates) {
//  coordinates_ = coordinates;
//}
void Entity::set_coordinates(int x, int y) {
  coordinates_.first = x;
  coordinates_.second = y;
}
void Entity::set_x(int x) { coordinates_.first = x; }
void Entity::set_y(int y) { coordinates_.second = y; }
void Entity::set_tile_size(int tile_size) { tile_size_ = tile_size; }
