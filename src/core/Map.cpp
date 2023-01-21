#include <memory>

#include <core/Map.hpp>

Map::Map(const SDL_Texture *floor, const SDL_Texture *wall, int width_,
         int height_)
    : width(width_), height(height_), texture_floor(floor), texture_wall(wall) {
  tiles.reserve(width * height);
}

void Map::initialise_default_map() {
  // Tile position is (c,r)
  for (int r = 0; r < ROWS; ++r) {
    for (int c = 0; c < COLS; ++c) {
      if (tiles_map[r * COLS + c] == '#') {
        tiles.emplace_back(std::make_unique<Tile>(texture_wall, TileType::WALL,
                                                  Position{c, r}));
      } else {
        tiles.emplace_back(std::make_unique<Tile>(
            texture_floor, TileType::FLOOR, Position{c, r}));
      }
    } // c < COLS
  }   // r < ROWS
}

int Map::get_width() { return width; }

int Map::get_height() { return height; }

bool Map::tile_has_actor(const Position pos) {
  return Map::get_tile(pos)->has_actor();
}

Actor *Map::tile_get_actor(const Position pos) {
  if(!Map::tile_has_actor(pos)) {
    return nullptr;
  }

  return Map::get_tile(pos)->get_actor();
}

std::vector<std::unique_ptr<Tile>> &Map::get_tiles() { return tiles; }

Tile *Map::get_tile(const Position &pos) const {
  auto [x, y] = pos;
  if ((x >= Map::height) || (y >= Map::width) || (x < 0) || (y < 0)) {
    SDL_Log("Attempting to index map out of range.\n");
    return nullptr;
  }
  return tiles[x * width + y].get();
}
