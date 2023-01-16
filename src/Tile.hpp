#ifndef TILE_HPP
#define TILE_HPP

#include "Entity.hpp"

enum class TileType { FLOOR, WALL, RESERVED };

class Tile : public Entity{
 public:
   Tile();
   Tile(enum TileType type);
   Tile(enum TileType, SDL_Texture *texture, SDL_Rect srcClip);
   bool is_walkable();
   void update();
 private:
   TileType type_;
   // Entity entities_; does it make sense to keep track of all
   // the entities in the tile itself, or somehow infer from the
   // world engine?
};
#endif /* ifndef SYMBOL */
