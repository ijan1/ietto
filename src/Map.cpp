#include "Map.hpp"

Map::Map(int x_, int y_, SDL_Texture *texWall, SDL_Texture *texFloor)
    : textureWall(texWall), textureFloor(texFloor), rows(x_), cols(y_) {
  map.resize(x_ * y_);
};

// Generates a boxed off map
void Map::box() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      set(i,j, Tile::FLOOR);
    }
  }

  for (int i = 0; i < cols; i++) {
    set(0, i, Tile::WALL);
    set(rows-1, i, Tile::WALL);
  }

  for (int i = 1; i < rows-1; i++) {
    set(i, 0, Tile::WALL);
    set(i, cols-1, Tile::WALL);
  }
}

