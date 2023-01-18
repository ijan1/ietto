#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <random>

#include "Entity.hpp"

enum class EnemyState {
  IDLE,
  WANDERING,
};

class Enemy : public Entity {
 public:
  Enemy(const SDL_Texture *texture, SDL_Rect srcClip);
  void update(Map *world);

 private:
  EnemyState state_;
  int health_;
};

#endif /* ifndef ENEMY_HPP */
