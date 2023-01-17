#include "Enemy.hpp"

Enemy::Enemy() : state_(EnemyState::IDLE), health_(100) {}
Enemy::Enemy(SDL_Texture *texture, SDL_Rect srcClip) : Entity(texture, srcClip) {};

void Enemy::update(Map *map) {
  if (state_ == EnemyState::WANDERING) {
//    int x = get_x_pos();
//    set_x_pos(x);
  }
}
