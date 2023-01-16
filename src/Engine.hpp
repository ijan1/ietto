#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "Entity.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "SDL.h"
#include "SDL_assert.h"
#include "SDL_image.h"

class Engine {
 public:
  Engine(const char *window_name, int window_width, int window_height);
  ~Engine();

  void run();

  void clear();
  void render(const Entity *entity);
  void render(const Map *map);
  void render(SDL_Texture *texture, SDL_Rect *srcClip, SDL_Rect *dstClip);
  void display();
  void destroy_window();
  void destroy_renderer();

  void initialise_map();
  Player *get_player() const;
  Map *get_map() const;

  SDL_Texture *load_SDL_Texture(const char *filepath);

  // std::pair doesn't convey much information here
  // we have the texture as the second element, but
  // what's the first one? id? name of place? type?

 private:
  int window_width_;
  int window_height_;
  const char *window_name_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  std::vector<SDL_Texture *> textures_;

  std::unique_ptr<Player> player_;
  std::unique_ptr<Map> map_;

  static bool instantiated_;

  // TODO: maybe have all the texture stored in a map in here,
  // and then each entity can request its own texture based on
  // json information
};

#endif /* ifndef ENGINE_HPP */
