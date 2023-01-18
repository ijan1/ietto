#include "Player.hpp"

Player::Player(const SDL_Texture *texture, const SDL_Rect &srcClip)
    : Actor(texture, srcClip), direction(Direction::IDLE) {}
Player::~Player() {}

void Player::set_stage(Map *stage_) {
  stage = stage_;
}

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
    case Direction::MOVE_NORTH:
      new_pos = new_pos + Position{-1, 0};
      break;
    case Direction::MOVE_SOUTH:
      new_pos = new_pos + Position{1, 0};
      break;
    case Direction::MOVE_EAST:
      new_pos = new_pos + Position{0, 1};
      break;
    case Direction::MOVE_WEST:
      new_pos = new_pos + Position{0, -1};
      break;
    case Direction::MOVE_NORTHEAST:
      new_pos = new_pos + Position{-1, 1};
      break;
    case Direction::MOVE_NORTHWEST:
      new_pos = new_pos + Position{-1, -1};
      break;
    case Direction::MOVE_SOUTHEAST:
      new_pos = new_pos + Position{1, 1};
      break;
    case Direction::MOVE_SOUTHWEST:
      new_pos = new_pos + Position{1, -1};
      break;
    case Direction::IDLE:
      break;
  }
  Player::direction = Direction::IDLE;

  if (stage->get_tile(new_pos)->is_walkable()) {
    Player::set_position(new_pos);
  } else {
    ;
  }
}
