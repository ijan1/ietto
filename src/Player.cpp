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
  auto [col, row] = Player::get_coordinates();
  switch (direction_) {
    case Direction::NORTH:
      row -= 1;
      break;
    case Direction::SOUTH:
      row += 1;
      break;
    case Direction::EAST:
      col += 1;
      break;
    case Direction::WEST:
      col -= 1;
      break;
    case Direction::IDLE:
      break;
    default:
      direction_ = Direction::IDLE;
      break;
  }

  // NOTE: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds or
  // index out of the map and crash the game
  // TODO: make method
  if (row < 0) row = 0;
  if (col < 0) col = 0;
  if (row > map->max_bound_row()) row = map->max_bound_row();
  if (col > map->max_bound_col()) col = map->max_bound_col();

  if (map->get_tile(row,col)->is_walkable()) {
    set_coordinates(row,col);
  } else {
    ;
  }

  direction_ = Direction::IDLE;
}
