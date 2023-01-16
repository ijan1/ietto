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

  auto tile_texture_floor =
      engine->load_SDL_Texture("resources/Objects/Tile.png");
  SDL_Rect tile_srcClip_floor{0, 0, 16, 16};
  std::vector<Tile *> tiles;
  tiles.reserve(40 * 30);
  for (int i = 0; i < 40; ++i) {
    for (int j = 0; j < 30; j++) {
      TileType type;
      Tile *tile = nullptr;
      if (tiles_[i] == '_') {
        type = TileType::FLOOR;
      } else {
        type = TileType::WALL;
      }
      tile = new Tile(type, tile_texture_floor, tile_srcClip_floor);
      tile->set_x_pos(i);
      tile->set_y_pos(j);
      tiles.emplace_back(tile);
    }
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
      player->update();

      if (ctr == 5) {
        game_running = false;
      }
      engine->clear();
      for(auto const &t : tiles) {
        engine->render(t);
      }
      engine->render(player.get());

      engine->display();
    }
  }
} // main
