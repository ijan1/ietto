#ifndef TILE_HPP
#define TILE_HPP

#include <memory>

#include "Enemy.hpp"
#include "Entity.hpp"

enum class TileType { FLOOR, WALL, RESERVED };

class Tile : public Entity {
 public:
  Tile(enum TileType, const SDL_Texture *texture, SDL_Rect srcClip);
  bool is_walkable();
  bool has_enemy();
  Enemy *get_enemy();
  void set_enemy(Enemy *enemy);
  void move_enemy_to(Tile *new_tile);
  void update(Map *map);

 private:
  TileType type_;
  Enemy *enemy_;
};
#endif /* ifndef SYMBOL */
