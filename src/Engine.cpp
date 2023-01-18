#include "Engine.hpp"

#include <memory>

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

  window_ = SDL_Window_ptr(SDL_CreateWindow(
      window_name_, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      window_width_, window_height_, SDL_WINDOW_SHOWN));
  if (!window_) {
    SDL_Log("Failed to initialise a window. Error: %s\n", SDL_GetError());
  }

  renderer_ = SDL_Renderer_ptr(
      SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_PRESENTVSYNC));
  if (!renderer_) {
    SDL_Log("Failed to initialise the renderer. Error: %s\n", SDL_GetError());
  }

  instantiated_ = true;
}

Engine::~Engine() {
  // Everything is wrapped in unique_ptrs, so
  // there shouldn't be anything left to be destroyed
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
        player_->handle_keypress(&event);
        player_->update(get_map());

        // Update enemies
        for (auto &e : enemies_) {
          e->update(get_map());
        }

        clear();
        render(get_map());
        render(get_player());
        display();
      }
    }
  }
}

const SDL_Texture *Engine::load_SDL_Texture(const char *filepath) {
  SDL_Texture *tex_ = nullptr;
  if (!filepath) {
    SDL_Log("An empty string has been passed\n.");
    return nullptr;
  }

  tex_ = IMG_LoadTexture(renderer_.get(), filepath);
  SDL_Texture_ptr texture_ = SDL_Texture_ptr(tex_);

  if (!tex_) {
    SDL_Log("Failed to load texture %s. Error: %s\n", filepath, SDL_GetError());
    return nullptr;
  }

  // TODO: figure out what's going on here
  // i can't return the smart pointer without
  // it going out of scope for some reason
  textures_.push_back(std::move(texture_));
  return tex_;
}

void Engine::clear() { SDL_RenderClear(renderer_.get()); }

void Engine::render(const Map *map) {
  for (auto &t : map->get_tiles()) {
    // Render the tile itself
    render(t);
    // Render any enemy on the tile
    render(t->get_enemy());
  }

  for (int x = 0; x < map->max_bound_x(); ++x) {
    for (int y = 0; y < map->max_bound_y(); ++y) {
      if (player_->get_x() == x && player_->get_y() == y) {
        printf("@");
      } else if (map->get_tile(x, y)->has_enemy()) {
        printf("e");
      } else if (map->get_tile(x, y)->is_walkable()) {
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
  if (entity == nullptr) {
    return;
  }

  int tile_size = entity->get_tile_size();
  int x = entity->get_x() * tile_size;
  int y = entity->get_y() * tile_size;
  // NOTE: this has to be flipped
  SDL_Rect dstClip{y, x, tile_size, tile_size};

  render(const_cast<SDL_Texture *>(entity->get_SDLTexture()),
         const_cast<SDL_Rect *>(entity->get_srcClip()), &dstClip);
}

void Engine::render(SDL_Texture *tex, SDL_Rect *srcClip, SDL_Rect *dstClip) {
  SDL_RenderCopy(renderer_.get(), tex, srcClip, dstClip);
}

void Engine::display() { SDL_RenderPresent(renderer_.get()); }

void Engine::initialise_map() {
  auto tile_texture_floor = load_SDL_Texture("resources/Objects/Tile.png");
  auto tile_texture_wall = load_SDL_Texture("resources/Objects/Wall.png");

  map_ = std::make_unique<Map>(tile_texture_floor, tile_texture_wall, nullptr);
}

void Engine::initialise_enemies() {
  constexpr int tex_size = 16;
  auto texture_enemy = load_SDL_Texture("resources/Characters/Player1.png");
  auto enemy_ = std::make_unique<Enemy>(texture_enemy,
                                        SDL_Rect{16, 16, tex_size, tex_size});
  map_->get_tile(1, 1)->set_enemy(enemy_.get());
  enemies_.push_back(std::move(enemy_));
}

Player *Engine::get_player() const { return player_.get(); }
Map *Engine::get_map() const { return map_.get(); }

bool Engine::instantiated_ = false; // Only 1 instance of Engine can exist
