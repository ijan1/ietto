#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actor.hpp"

class Enemy : public Actor {
 public:
  Enemy(const SDL_Texture *texture, const SDL_Rect &srcClip);
  ~Enemy() override = default;

  void update() override;

 private:
};

#endif /* ENEMY_HPP */
