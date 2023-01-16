#include "Map.hpp"

constexpr int TEXTURE_SIZE = 16;

Map::Map(SDL_Texture *texture_floor, SDL_Texture *texture_wall,
         SDL_Texture *texture_water)
    : texture_floor_(texture_floor),
      texture_wall_(texture_wall),
      texture_water_(texture_water) {

  SDL_Log("Initialising default map from tiles.hpp");

  tiles_.reserve(ROWS * COLS);
  dimensions_ = {ROWS, COLS};

  SDL_Rect tile_srcClip_floor{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
  SDL_Rect tile_srcClip_wall{16, 64, TEXTURE_SIZE, TEXTURE_SIZE};
  for (int rows = 0; rows < 30; ++rows) {
    for (int cols = 0; cols < 40; ++cols) {
      TileType type;
      Tile *tile = nullptr;
      if (tiles_map[rows * 40 + cols] == '_') {
        type = TileType::FLOOR;
        tile = new Tile(type, texture_floor_, tile_srcClip_floor);
      } else {
        type = TileType::WALL;
        tile = new Tile(type, texture_wall_, tile_srcClip_wall);
      }
      tile->set_x_pos(cols);
      tile->set_y_pos(rows);
      tiles_.emplace_back(tile);
    }
  }
}

std::vector<Tile *> Map::get_tiles() const {
  return tiles_;
}

Tile *Map::get_tile(int x, int y) const {
  if (x >= max_bound_row() || y >= max_bound_col()) {
    SDL_Log("Attempting to get non-existent tile.");
    return nullptr;
  }

  return tiles_[x*max_bound_col()+y];
}

int Map::max_bound_row() const {
  return dimensions_.first;
}

int Map::max_bound_col() const {
  return dimensions_.second;
}

