#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"
#include "tiles.hpp"

class Map {
 public:
  Map(const SDL_Texture *texture_floor, const SDL_Texture *texture_wall,
      const SDL_Texture *texture_water);

  std::vector<Tile *> &get_tiles();
  Tile *get_tile(int x, int y) const;
  void set_tile(int x, int y, Tile *tile);
  int max_bound_x() const;
  int max_bound_y() const;

 private:
  // TODO: combine all of these different
  // sprites into one atlas so that it can
  // be loaded in at once
  const SDL_Texture *texture_floor_;
  const SDL_Texture *texture_wall_;
  const SDL_Texture *texture_water_;

  std::pair<int, int> dimensions_;
  std::vector<Tile *> tiles_;
};

#endif /* ifndef MAP_HPP */
