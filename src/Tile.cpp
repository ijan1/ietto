#include "Tile.hpp"

#include <memory>

Tile::Tile(TileType type, const SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip), type_(type), enemy_(nullptr) {}

bool Tile::is_walkable() {
  switch (type_) {
    case TileType::FLOOR:
      return true;
    case TileType::WALL:
      return false;
    default:
      return false;
  }
}

bool Tile::has_enemy() {
  if (enemy_) {
    return true;
  }

  return false;
}

Enemy *Tile::get_enemy() { return enemy_; }

void Tile::set_enemy(Enemy *enemy) { enemy_ = enemy; }

void Tile::move_enemy_to(Tile *new_tile) {
  new_tile->set_enemy(enemy_);
  enemy_ = nullptr;
}

void Tile::update(Map *map) { (void)map; }
