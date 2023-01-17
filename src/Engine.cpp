#include "Engine.hpp"
#include "SDL_events.h"

Engine::Engine(const char *window_name, int w, int h)
    : window_width_(w),
      window_height_(h),
      window_name_(window_name),
      window_(nullptr),
      renderer_(nullptr),
      map_(nullptr) {
  SDL_assert(instantiated_ == false);

  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
  }

  int IMG_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (IMG_Init(IMG_init_flags) != IMG_init_flags) {
    SDL_Log("Failed to initialise IMG_Init. Error: %s\n", SDL_GetError());
  }

  window_ = SDL_CreateWindow(window_name_, SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, window_width_,
                             window_height_, SDL_WINDOW_SHOWN);
  if (!window_) {
    SDL_Log("Failed to initialise a window. Error: %s\n", SDL_GetError());
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
  if (!renderer_) {
    SDL_Log("Failed to initialise the renderer. Error: %s\n", SDL_GetError());
  }

  instantiated_ = true;
}

Engine::~Engine() {
  destroy_window();
  destroy_renderer();

  for (auto t : textures_) {
    SDL_DestroyTexture(t);
  }

  instantiated_ = false;
}

void Engine::run() {
  constexpr int tex_size = 16;
  auto texture_player = load_SDL_Texture("resources/Characters/Player1.png");
  player_ = std::make_unique<Player>(texture_player,
                                     SDL_Rect{0, 0, tex_size, tex_size});

  SDL_Event event;
  bool game_running = true;

  while (game_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
          game_running = false;
        }
      }
      player_->handle_keypress(&event);
      player_->update(get_map());

      clear();
      render(get_map());
      render(get_player());
      display();
    }
  }
}

SDL_Texture *Engine::load_SDL_Texture(const char *filepath) {
  SDL_Texture *tex_ = nullptr;

  if (!filepath) {
    SDL_Log("An empty string has been passed\n.");
  }
  tex_ = IMG_LoadTexture(renderer_, filepath);

  if (!tex_) {
    SDL_Log("Failed to load texture %s. Error: %s\n", filepath, SDL_GetError());
    return nullptr;
  }

  textures_.emplace_back(tex_);
  return tex_;
}

void Engine::clear() { SDL_RenderClear(renderer_); }

void Engine::render(const Map *map) {
  for (auto &t : map->get_tiles()) {
    render(t);
  }

  for (int i = 0; i < map->max_bound_row(); ++i) {
    for (int j = 0; j < map->max_bound_col(); ++j) {
      if (player_->get_x_pos() == j && player_->get_y_pos() == i) {
        printf("@");
      } else if (map->get_tile(i, j)->is_walkable()) {
        printf("_");
      } else {
        printf("#");
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

void Engine::render(const Entity *entity) {
  int tile_size = entity->get_tile_size();
  int x = entity->get_x_pos() * tile_size;
  int y = entity->get_y_pos() * tile_size;
  SDL_Rect dstClip{x, y, tile_size, tile_size};

  render(const_cast<SDL_Texture *>(entity->get_SDLTexture()),
         const_cast<SDL_Rect *>(entity->get_srcClip()),
         &dstClip);
}

void Engine::render(SDL_Texture *tex, SDL_Rect *srcClip, SDL_Rect *dstClip) {
  SDL_RenderCopy(renderer_, tex, srcClip, dstClip);
}

void Engine::display() { SDL_RenderPresent(renderer_); }

void Engine::destroy_window() { SDL_DestroyWindow(window_); }

void Engine::destroy_renderer() { SDL_DestroyRenderer(renderer_); }

void Engine::initialise_map() {
  auto tile_texture_floor = load_SDL_Texture("resources/Objects/Tile.png");
  auto tile_texture_wall = load_SDL_Texture("resources/Objects/Wall.png");

  map_ = std::make_unique<Map>(tile_texture_floor, tile_texture_wall, nullptr);
}

Player *Engine::get_player() const { return player_.get(); }
Map *Engine::get_map() const { return map_.get(); }

bool Engine::instantiated_ = false; // Only 1 instance of Engine can exist
