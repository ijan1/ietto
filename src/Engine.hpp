#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "SDL.h"
#include "SDL_assert.h"
#include "SDL_image.h"

struct SDL_TextureDestroyer {
  void operator()(SDL_Texture *p) { SDL_DestroyTexture(p); }
};
struct SDL_WindowDestroyer {
  void operator()(SDL_Window *p) { SDL_DestroyWindow(p); }
};
struct SDL_RendererDestroyer {
  void operator()(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
};

using SDL_Texture_ptr = std::unique_ptr<SDL_Texture, SDL_TextureDestroyer>;
using SDL_Window_ptr = std::unique_ptr<SDL_Window, SDL_WindowDestroyer>;
using SDL_Renderer_ptr = std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer>;

class Engine {
 public:
  Engine(const char *window_name, int window_width, int window_height);
  ~Engine();

  void run();
  void initialise_enemies();
  void initialise_map();

 private:
  void clear();
  void render(const Entity *entity);
  void render(Map *map);
  void render(SDL_Texture *texture, SDL_Rect *srcClip, SDL_Rect *dstClip);
  void display();

  Map *get_map() const;
  Player *get_player() const;

  const SDL_Texture *load_SDL_Texture(const char *filepath);

  int window_width_;
  int window_height_;
  const char *window_name_;
  SDL_Window_ptr window_;
  SDL_Renderer_ptr renderer_;

  std::vector<SDL_Texture_ptr> textures_;

  std::unique_ptr<Map> map_;
  std::unique_ptr<Player> player_;
  std::vector<std::unique_ptr<Enemy>> enemies_;

  static bool instantiated_;
};

#endif /* ifndef ENGINE_HPP */
