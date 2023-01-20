#include "player/Player.hpp"

#include "SDL_log.h"

Player::Player(const SDL_Texture *texture, const SDL_Rect &srcClip)
    : Actor(texture, srcClip, "Player"), direction(Direction::IDLE) {}

void Player::handle_keypress(SDL_Event &e) {
  switch (e.type) {
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
        case SDLK_w:
          direction = direction | Direction::MOVE_NORTH;
          break;
        case SDLK_s:
          direction = direction | Direction::MOVE_SOUTH;
          break;
        case SDLK_d:
          direction = direction | Direction::MOVE_EAST;
          break;
        case SDLK_a:
          direction = direction | Direction::MOVE_WEST;
          break;
      }
  }
}

void Player::update() {
  Position new_pos = Player::get_position();
  switch (direction) {
    using enum Direction;
    case MOVE_NORTH:
      new_pos = new_pos + Position{-1, 0};
      break;
    case MOVE_SOUTH:
      new_pos = new_pos + Position{1, 0};
      break;
    case MOVE_EAST:
      new_pos = new_pos + Position{0, 1};
      break;
    case MOVE_WEST:
      new_pos = new_pos + Position{0, -1};
      break;
    default:
      break;
  }
  Player::direction = Direction::IDLE;

  if (stage->tile_has_actor(new_pos)) {
    // TODO: the log message has to be in 'Combat'
    // too much indirection happening here
    SDL_LogMessage(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_INFO,
                   "You got into combat with %s\n",
                   stage->get_tile(new_pos)->get_actor()->get_name().data());
  }

  if (Player::can_move_to(new_pos)) {
    Player::move_to(new_pos);
  }
}
