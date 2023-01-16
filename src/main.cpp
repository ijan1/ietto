#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

#include "Engine.hpp"
#include "Entity.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TEXTURE_SIZE = 16;

int main(int argc, char *args[]) {
  auto engine = std::make_unique<Engine>("dumb game_running", SCREEN_WIDTH,
                                         SCREEN_HEIGHT);

  auto texture_player =
      engine->load_SDL_Texture("resources/Characters/Player1.png");
  auto player = std::make_unique<Entity>(
      texture_player, SDL_Rect{0, 0, TEXTURE_SIZE, TEXTURE_SIZE});

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
      engine->render(player.get());
      engine->display();
    }
  }
} // main
