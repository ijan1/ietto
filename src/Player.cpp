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

void Player::update(std::vector<Entity *> &world) {
  // NOTE: coordinates are kept in a
  auto [x, y] = Player::get_coordinates();
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

  // XXX: keep some kind of saturation arithmetic here
  // so that the player can't go out of bounds or
  // index out of the map and crash the game
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x > 40) y = 40;
  if (y > 30) x = 30;

  Tile *tile = static_cast<Tile *>(world[y * 40 + x]);
  if (tile->is_walkable()) {
    set_coordinates(x,y);
  } else {
    ;
  }

  for (int i = 0; i < 30; ++i) {
    for (int j = 0; j < 40; j++) {
      if (x == j && y == i) {
        printf("@");
      } else if (static_cast<Tile *>(world[i * 40 + j])->is_walkable()) {
        printf("_");
      } else {
        printf("#");
      }
    }
    printf("\n");
  }
  printf("\n\n");

  direction_ = Direction::IDLE;
}
