#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

#include "core/Engine.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  (void)argc;
  (void)args;

  auto engine = std::make_unique<Engine>("dumb game_running", SCREEN_WIDTH,
                                         SCREEN_HEIGHT);
  engine->run();
} // main
