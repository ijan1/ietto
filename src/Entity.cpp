#include "Entity.hpp"

#include "SDL_keycode.h"

Entity::Entity(SDL_Texture *texture, SDL_Rect srcClip)
    : coordinates_(0, 0),
      texture_(texture), // NOTE: Assuming that h = w
      srcClip_(srcClip),
      tile_size_(srcClip.h) {}

const SDL_Texture *Entity::get_SDLTexture() const { return texture_; }

const SDL_Rect *Entity::get_srcClip() const { return &srcClip_; }

int Entity::get_x_pos() const { return coordinates_.first; }

int Entity::get_y_pos() const { return coordinates_.second; }

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

void Entity::set_srcClip(int x, int y) {
  srcClip_.x = x;
  srcClip_.y = y;
}

void Entity::handle_keypress(SDL_Event *e) {
  switch (e->type) {
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym) {
        case SDLK_w:
          direction_ = Direction::NORTH;
          break;
        case SDLK_s:
          direction_ = Direction::SOUTH;
          break;
        case SDLK_d:
          direction_ = Direction::EAST;
          break;
        case SDLK_a:
          direction_ = Direction::WEST;
          break;
      }
  }
}

void Entity::update() {
  switch(direction_) {
    case Direction::NORTH:
      coordinates_.second -= 1;
      break;
    case Direction::SOUTH:
      coordinates_.second += 1;
      break;
    case Direction::EAST:
      coordinates_.first += 1;
      break;
    case Direction::WEST:
      coordinates_.first -= 1;
      break;
  }
  direction_ = Direction::IDLE;
}
