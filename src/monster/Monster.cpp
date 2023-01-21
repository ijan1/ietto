#include "monster/Monster.hpp"

Monster::Monster(const SDL_Texture *texture, const SDL_Rect &srcClip)
    : Actor(texture, srcClip) {}

void Monster::update() {
  auto pos = Monster::get_position();

  if (Monster::can_move_to(pos)) {
    Monster::move_to(pos);
  }
}
