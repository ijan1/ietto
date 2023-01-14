#include <vector>
#include "SDL_image.h"

enum class Tile { WALL, FLOOR };

class Map {
 private:
  std::vector<Tile> map;
  SDL_Texture *textureWall;
  SDL_Texture *textureFloor;

 public:
  int rows, cols;
  Map(int x, int y, SDL_Texture *texWall, SDL_Texture *texFloor);
  inline Tile get(int x_, int y_) {return map[x_*cols+y_];};
  inline void set(int x_, int y_, Tile tile) {map[x_*cols+y_] = tile;};
  void box();
};
