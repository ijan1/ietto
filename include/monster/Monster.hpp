#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "core/Actor.hpp"

class Monster : public Actor {
 public:
  Monster(const SDL_Texture *texture, const SDL_Rect &srcClip);
  ~Monster() override = default;

  constexpr bool is_monster() override { return true; }
  void update() override;

 private:
};

#endif /* ENEMY_HPP */
