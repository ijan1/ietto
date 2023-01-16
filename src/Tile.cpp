#include "Tile.hpp"

Tile::Tile() : type_(TileType::RESERVED){};
Tile::Tile(TileType type) : type_(type) {}
Tile::Tile(TileType type, SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip), type_(type) {}

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

void Tile::update(std::vector<Entity *> &world) { (void)world; }
