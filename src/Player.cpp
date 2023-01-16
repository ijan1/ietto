#include "Player.hpp"

Player::Player() : health(100) {}
Player::Player(SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip) {}

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

void Player::update(std::vector<Entity *> &world) {
  auto [x, y] = coordinates_;
  SDL_Log("Coordinates pre-move: %d:%d\n", x,y);

  switch (direction_) {
    case Direction::NORTH:
      y -= 1;
      break;
    case Direction::SOUTH:
      y += 1;
      break;
    case Direction::EAST:
      x += 1;
      break;
    case Direction::WEST:
      x -= 1;
      break;
    case Direction::IDLE:
      break;
    default:
      direction_ = Direction::IDLE;
      break;
  }

  // TODO: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x > 30) x = 30;
  if (y > 40) y = 40;

  Entity *tile = world[x * 30 + y];
  if (static_cast<Tile *>(tile)->is_walkable()) {
    coordinates_ = {x, y};
  } else {
    ;
  }
  direction_ = Direction::IDLE;
  SDL_Log("Coordinates post-move: %d:%d\n\n", x,y);
}
