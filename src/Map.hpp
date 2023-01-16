#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"
#include "tiles.hpp"

class Map {
  public:
    Map(SDL_Texture *texture_floor, SDL_Texture *texture_wall, SDL_Texture *texture_water);

    std::vector<Tile *> get_tiles() const ;
    Tile *get_tile(int x, int y) const;
    void set_tile(int x, int y, Tile *tile);
    int max_bound_row() const ;
    int max_bound_col() const;

  private:
    // TODO: combine all of these different
    // sprites into one atlas so that it can
    // be loaded in at once
    SDL_Texture *texture_floor_;
    SDL_Texture *texture_wall_;
    SDL_Texture *texture_water_;

    std::pair<int,int> dimensions_;
    std::vector<Tile *> tiles_;
};

#endif /* ifndef MAP_HPP */
