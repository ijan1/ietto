#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

#include "Engine.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "tiles.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  auto engine = std::make_unique<Engine>("dumb game_running", SCREEN_WIDTH,
                                         SCREEN_HEIGHT);

  engine->initialise_map();
  engine->initialise_enemies();
  engine->run();
} // main
