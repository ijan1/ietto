#include "Player.hpp"

Player::Player() : health(100) {}
Player::Player(SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip)
{
  set_coordinates(40/2, 30/2);
}

void Player::handle_keypress(SDL_Event *e) {
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

void Player::update(Map *map) {
  // NOTE: coordinates are kept in a
  auto [r, c] = Player::get_coordinates();
  switch (direction_) {
    case Direction::NORTH:
      r -= 1;
      break;
    case Direction::SOUTH:
      r += 1;
      break;
    case Direction::EAST:
      c += 1;
      break;
    case Direction::WEST:
      c -= 1;
      break;
    case Direction::IDLE:
      break;
    default:
      direction_ = Direction::IDLE;
      break;
  }

  // XXX: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds or
  // index out of the map and crash the game
  // TODO: make method
  if (r < 0) r = 0;
  if (c < 0) c = 0;
  if (r > map->max_bound_row()) r = map->max_bound_row();
  if (c > map->max_bound_col()) c = map->max_bound_col();

  if (map->get_tile(r,c)->is_walkable()) {
    set_coordinates(r,c);
  } else {
    ;
  }

  direction_ = Direction::IDLE;
}
