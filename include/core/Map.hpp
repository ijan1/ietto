#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "core/Tile.hpp"
#include "tiles.h"

class Map {
 public:
  Map(const SDL_Texture *floor, const SDL_Texture *wall, int width = COLS,
      int height = ROWS);

  void initialise_default_map();

  int get_width();
  int get_height();

  bool tile_has_actor(const Position pos);

  std::vector<std::unique_ptr<Tile>> &get_tiles();
  Tile *get_tile(const Position &pos) const;
  void set_tile(Tile &&t); // NOTE: is this right?

 private:
  // TODO: maybe pick better names?
  int width;
  int height;
  std::vector<std::unique_ptr<Tile>> tiles;

  // Engine should have ownership of the textures
  const SDL_Texture *texture_floor;
  const SDL_Texture *texture_wall;
};

#endif /* MAP_HPP */
