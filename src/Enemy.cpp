#include "Enemy.hpp"

#include <random>

Enemy::Enemy(const SDL_Texture *texture, const SDL_Rect &srcClip)
    : Actor(texture, srcClip) {}

void Enemy::update() {
  auto pos = Enemy::get_position();

  //  std::random_device rd;
  //  std::mt19937 gen(rd());
  //  std::uniform_int_distribution<> distrib(1, 20);
  //
  //  int result = distrib(gen);
  //  if (result > 15) {
  //    pos = pos + Position{0, 1};
  //  } else if (result > 10) {
  //    pos = pos + Position{0, -1};
  //  } else if (result > 5) {
  //    pos = pos + Position{1, 0};
  //  } else {
  //    pos = pos + Position{-11, 0};
  //  }

  if (Enemy::can_move_to(pos)) {
    Enemy::move_to(pos);
  }
}
