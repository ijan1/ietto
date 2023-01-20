#include "monster/Monster.hpp"

Enemy::Enemy(const SDL_Texture *texture, const SDL_Rect &srcClip)
    : Actor(texture, srcClip) {}

void Enemy::update() {
  auto pos = Enemy::get_position();

  if (Enemy::can_move_to(pos)) {
    Enemy::move_to(pos);
  }
}
