#include "Map.hpp"

constexpr int TEXTURE_SIZE = 16;

Map::Map(const SDL_Texture *texture_floor, const SDL_Texture *texture_wall,
         const SDL_Texture *texture_water)
    : texture_floor_(texture_floor),
      texture_wall_(texture_wall),
      texture_water_(texture_water) {
  SDL_Log("Initialising default map from tiles.hpp");

  tiles_.reserve(ROWS * COLS);
  dimensions_ = {ROWS, COLS};

  SDL_Rect tile_srcClip_floor{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
  SDL_Rect tile_srcClip_wall{16, 64, TEXTURE_SIZE, TEXTURE_SIZE};
  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      TileType type;
      // TODO, use emplace on 'tiles_' to construct the tile
      // in-place rather than having explicit constructors in each
      // branch of the if
      Tile *tile = nullptr;
      if (tiles_map[row * COLS + col] == '_') {
        type = TileType::FLOOR;
        tile = new Tile(type, texture_floor_, tile_srcClip_floor);
      } else {
        type = TileType::WALL;
        tile = new Tile(type, texture_wall_, tile_srcClip_wall);
      }
      tile->set_x(row);
      tile->set_y(col);
      tiles_.push_back(tile);
    }
  }
}

std::vector<Tile *> Map::get_tiles() const { return tiles_; }

Tile *Map::get_tile(int x, int y) const {
  if (x >= max_bound_x() || y >= max_bound_y()) {
    SDL_Log("Attempting to get non-existent tile.");
    return nullptr;
  }

  return tiles_[x * max_bound_y() + y];
}

int Map::max_bound_x() const { return dimensions_.first; }

int Map::max_bound_y() const { return dimensions_.second; }
