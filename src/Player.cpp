#include "Player.hpp"

Player::Player(const SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip) {
  set_coordinates({40 / 2, 30 / 2});
}

void Player::handle_keypress(SDL_Event *e) {
  switch (e->type) {
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym) {
        case SDLK_w:
          state_ = PlayerState::MOVE_NORTH;
          break;
        case SDLK_s:
          state_ = PlayerState::MOVE_SOUTH;
          break;
        case SDLK_d:
          state_ = PlayerState::MOVE_EAST;
          break;
        case SDLK_a:
          state_ = PlayerState::MOVE_WEST;
          break;
      }
  }
}

void Player::update(Map *map) {
  // NOTE: it's better to think of this as (row,col), rather
  // than coordinates in a point
  auto [x, y] = Player::get_coordinates();
  switch (state_) {
    case PlayerState::MOVE_NORTH:
      x -= 1;
      break;
    case PlayerState::MOVE_SOUTH:
      x += 1;
      break;
    case PlayerState::MOVE_EAST:
      y += 1;
      break;
    case PlayerState::MOVE_WEST:
      y -= 1;
      break;
    default:
      state_ = PlayerState::IDLE;
      break;
  }

  // NOTE: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds or
  // index out of the map and crash the game
  y = std::max(0, y);
  x = std::max(0, x);
  y = std::min(y, map->max_bound_y());
  x = std::min(x, map->max_bound_x());

  if (map->get_tile(x, y)->has_enemy()) {
    SDL_Log("You got into a fight.");
  } else if (map->get_tile(x, y)->is_walkable()) {
    set_coordinates({x, y});
  } else {
    ;
  }

  state_ = PlayerState::IDLE;
}
