#include "Player.hpp"

Player::Player(const SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip) {
  set_coordinates(40 / 2, 30 / 2);
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
  // NOTE: coordinates are kept in a
  auto [row, col] = Player::get_coordinates();
  switch (state_) {
    case PlayerState::MOVE_NORTH:
      row -= 1;
      break;
    case PlayerState::MOVE_SOUTH:
      row += 1;
      break;
    case PlayerState::MOVE_EAST:
      col += 1;
      break;
    case PlayerState::MOVE_WEST:
      col -= 1;
      break;
    default:
      state_ = PlayerState::IDLE;
      break;
  }

  // NOTE: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds or
  // index out of the map and crash the game
  col = std::max(0, col);
  row = std::max(0, row);
  col = std::min(col, map->max_bound_x());
  row = std::min(row, map->max_bound_y());

  if (map->get_tile(row, col)->has_enemy()) {
    SDL_Log("You got into a fight.");
  } else if (map->get_tile(row, col)->is_walkable()) {
    SDL_Log("Moved to coordinates: %d:%d\n", row,col);
    set_coordinates(row, col);
  } else {
    ;
  }

  state_ = PlayerState::IDLE;
}
