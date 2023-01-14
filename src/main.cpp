#include <cstdio>
#include <cstdlib>
#include <memory>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_ttf.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
  }

  int IMG_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (IMG_Init(IMG_init_flags) != IMG_init_flags) {
    SDL_Log("Failed to initialise IMG_Init. Error: %s\n", SDL_GetError());
  }

  const int tex_size = 16;
  auto window =
      std::make_unique<RenderWindow>("Test game", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Texture *player_texture = window->loadTexture("resources/Characters/Humanoid0.png");
  // First two positions for the rect are the starting position,
  // the latter two are the size/dimensions of the tile
  SDL_Rect srcRect{32, 32, 16, 16};

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
      }
      else if (event.type == SDL_KEYDOWN){
        player->update(event);
      }
    }
    window->clear();
    window->render(player_texture, &srcRect, player->get_frame());
    window->display();
  }

  SDL_Quit();
  return 0;
}
