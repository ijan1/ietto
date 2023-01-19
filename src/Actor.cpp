#include "Actor.hpp"

#include "Map.hpp"
#include "Position.hpp"

Actor::Actor(const SDL_Texture *texture_, const SDL_Rect &srcClip_)
    : health(100),
      maxHealth(100),
      position{1, 1},
      texture(texture_),
      srcClip(srcClip_) {}
Actor::~Actor() = default;

int Actor::get_current_health() const { return health; }
void Actor::set_current_health(const int health_) { health = health_; }
int Actor::get_max_health() const { return maxHealth; }
void Actor::set_max_health(const int maxHealth_) { maxHealth = maxHealth_; }
const Position Actor::get_position() const { return position; }
void Actor::set_position(const Position position_) { position = position_; }

bool Actor::can_move_to(const Position pos) {
  auto tile = stage->get_tile(pos);
  if (!tile) {
    return false;
  }
  return tile->is_walkable();
}
void Actor::move_to(const Position pos) {
  stage->get_tile(get_position())->set_actor(nullptr);
  stage->get_tile(pos)->set_actor(this);
  Actor::set_position(pos);
}

Map *Actor::get_stage() const { return stage; }
void Actor::set_stage(Map *stage_) { stage = stage_; }

const SDL_Texture *Actor::get_Texture() const { return texture; }
void Actor::set_Texture(SDL_Texture *texture_) { texture = texture_; }
const SDL_Rect Actor::get_srcClip() const { return srcClip; }
void Actor::set_srcClip(const SDL_Rect &srcClip_) {
  // Which one?
  srcClip = srcClip_;
  // srcClip.h = srcClip_.h;
  // srcClip.w = srcClip_.w;
  // srcClip.x = srcClip_.x;
  // srcClip.y = srcClip_.y;
}

Map *Actor::stage = nullptr;
