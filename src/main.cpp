#include <cstdio>
#include <cstdlib>
#include <memory>

#include "Entity.hpp"
#include "Map.hpp"
#include "RenderWindow.hpp"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_ttf.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TEXTURE_SIZE = 16;

namespace SDL {
void init() {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
  }

  int IMG_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (IMG_Init(IMG_init_flags) != IMG_init_flags) {
    SDL_Log("Failed to initialise IMG_Init. Error: %s\n", SDL_GetError());
  }
} // SDL::init()
} // namespace SDL

int main(int argc, char *args[]) {
  SDL::init();
  auto window =
      std::make_unique<RenderWindow>("Test game", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Texture *player_texture =
      window->loadTexture("resources/Characters/Humanoid0.png");
  SDL_Texture *floor_texture =
      window->loadTexture("resources/Objects/Floor.png");
  SDL_Texture *wall_texture = window->loadTexture("resources/Objects/Wall.png");
  SDL_Rect srcRectPlayer{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
  SDL_Rect srcRectFloor{16, 96, TEXTURE_SIZE, TEXTURE_SIZE};
  SDL_Rect srcRectWall{16, 56, TEXTURE_SIZE, TEXTURE_SIZE};

  auto map = std::make_unique<Map>(40, 30, wall_texture, floor_texture);
  map->box();
  auto player = std::make_unique<Entity>(0, 0, player_texture);

  bool game_running = true;
  SDL_Event event;

  auto ctr = 0;
  while (game_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_Log("Registered mouse event.\n");
        ctr++;

        if (ctr == 5) {
          game_running = false;
        }
      } else if (event.type == SDL_KEYDOWN) {
        player->update(event);
      }
    }
    window->clear();
    SDL_Rect terrain{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
    for (int i = 0; i < map->rows; ++i) {
      for (int j = 0; j < map->cols; ++j) {
        if (map->get(i, j) == Tile::FLOOR) {
          window->render(floor_texture, &srcRectFloor, &terrain);
        } else if (map->get(i,j) == Tile::WALL){
          window->render(wall_texture, &srcRectWall, &terrain);
        }
        terrain.y += 16;
      }
      terrain.y = 0;
      terrain.x += 16;
    }
    window->render(player_texture, &srcRectPlayer, player->get_frame());
    window->display();
  }

  window->destroy();
  SDL_Quit();
  return 0;
}
