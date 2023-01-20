#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <memory>
#include <vector>

#include "SDL_wrappers.hpp"
#include "core/Actor.hpp"
#include "core/Map.hpp"
#include "monster/Monster.hpp"
#include "player/Player.hpp"

class Engine {
 public:
  Engine(const char *window_name, int width, int height);
  ~Engine();

  void init_stage();
  void init_player();
  void init_enemy();

  void run();
  void render();
  void update();

  const SDL_Texture *load_texture(const char *filepath);

 private:
  void clear();
  void display() const;

  void render(const Actor &game_actor) const;
  void render(const Tile &tile) const;
  void render(const SDL_Texture *texture, const SDL_Rect &srcClip,
              const SDL_Rect &dst) const;

 private:
  int window_width;
  int window_height;
  const char *window_name;

  SDL_Event event;
  static bool game_running;
  static constexpr float GAME_FPS = 60.0;
  static uint32_t start_time, end_time, delta_time;

  SDL::Window_ptr window;
  SDL::Renderer_ptr renderer;
  std::vector<SDL::Texture_ptr> textures;

  std::unique_ptr<Player> player;
  std::vector<std::unique_ptr<Actor>> enemies; // used for event queue
  std::unique_ptr<Map> stage;

  static bool instantiated;
};

#endif /* RESOURCEMANAGER_HPP */
