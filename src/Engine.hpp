#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>
#include <map>
#include <tuple>
#include <string>

#include "SDL.h"
#include "SDL_assert.h"
#include "SDL_image.h"

#include "Entity.hpp"

class Engine {
 public:
  Engine(const char *window_name, const int window_width, const int window_height);
  ~Engine();

  void clear();
  void render(const Entity *entity);
  void render(SDL_Texture *texture, SDL_Rect *srcClip, SDL_Rect *dstClip);
  void display();

  void destroy_window();
  void destroy_renderer();

  SDL_Texture *load_SDL_Texture(const char *filepath);

  std::vector<std::pair<std::string, SDL_Texture *>> textures_;

 private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  int window_width_;
  int window_height_;
  const char *window_name_;

  static bool instantiated_;

  // TODO: maybe have all the texture stored in a map in here,
  // and then each entity can request its own texture based on
  // json information

};

#endif /* ifndef ENGINE_HPP */
