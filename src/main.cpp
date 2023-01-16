#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

#include "Engine.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "tiles.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TEXTURE_SIZE = 16;

int main(int argc, char *args[]) {
  auto engine = std::make_unique<Engine>("dumb game_running", SCREEN_WIDTH,
                                         SCREEN_HEIGHT);

  auto texture_player =
      engine->load_SDL_Texture("resources/Characters/Player1.png");
  auto player = std::make_unique<Player>(
      texture_player, SDL_Rect{0, 0, TEXTURE_SIZE, TEXTURE_SIZE});
  player->set_x_pos(1);
  player->set_y_pos(1);

  auto tile_texture_floor =
      engine->load_SDL_Texture("resources/Objects/Tile.png");
  auto tile_texture_wall =
      engine->load_SDL_Texture("resources/Objects/Wall.png");
  SDL_Rect tile_srcClip_floor{0, 0, 16, 16};
  SDL_Rect tile_srcClip_wall{16, 64, 16, 16};
  std::vector<Entity *> tiles;
  tiles.reserve(40 * 30);
  for (int rows = 0; rows < 30; ++rows) {
    for (int cols = 0; cols < 40; cols++) {
      TileType type;
      Tile *tile = nullptr;
      if (tiles_[rows * 40 + cols] == '_') {
        type = TileType::FLOOR;
        tile = new Tile(type, tile_texture_floor, tile_srcClip_floor);
      } else {
        type = TileType::WALL;
        tile = new Tile(type, tile_texture_wall, tile_srcClip_wall);
      }
      tile->set_x_pos(cols);
      tile->set_y_pos(rows);
      tiles.emplace_back(tile);
      printf("%c", tiles_[rows*40+cols]);
    }
    printf("\n");
  }

  SDL_Event event;
  bool game_running = true;
  int ctr = 0;

  while (game_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_Log("Registered mouse event.\n");
        ctr++;
      }
      player->handle_keypress(&event);
      player->update(tiles);

      if (ctr == 5) {
        game_running = false;
      }
      engine->clear();
      for (auto const &t : tiles) {
        engine->render(t);
      }
      engine->render(player.get());

      engine->display();
    }
  }
} // main
