#include "Engine.hpp"

#include <memory>

constexpr int TEXTURE_SIZE = 16;

Engine::Engine(const char *name_, int width_, int height_)
    : window_width(width_),
      window_height(height_),
      window_name(name_),
      window(nullptr),
      renderer(nullptr),
      player(nullptr) {
  SDL_assert(instantiated == false);

  init_SDL();

  window = SDL_Window_ptr(SDL_CreateWindow(
      window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      window_width, window_height, SDL_WINDOW_SHOWN));
  if (!window) {
    SDL_Log("Failed to initialise a window. Error: %s\n", SDL_GetError());
  }

  // TODO: look into the following:
  // Disable VSYNC because performance plummets when using mouse and
  // and keyboard
  renderer = SDL_Renderer_ptr(
      SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC));
  if (!renderer) {
    SDL_Log("Failed to initialise the renderer. Error: %s\n", SDL_GetError());
  }

  instantiated = true;
  SDL_Log("Instantiated engine.");
}

Engine::~Engine() { instantiated = false; }

void Engine::init_stage() {
  const SDL_Texture *texture_floor =
      Engine::load_texture("resources/Objects/Tile.png");
  const SDL_Texture *texture_wall =
      Engine::load_texture("resources/Objects/Wall.png");
  stage = std::make_unique<Map>(texture_floor, texture_wall);
  stage->initialise_default_map();
  SDL_Log("Initialised default stage. Stage size: %zu\n",
          stage->get_tiles().size());
}

void Engine::init_player() {
  SDL_Rect srcClip{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
  const SDL_Texture *texture_player =
      Engine::load_texture("resources/Characters/Player0.png");
  player = std::make_unique<Player>(texture_player, srcClip);
  player->set_stage(stage.get());
  SDL_Log("Initialised player.");
}

void Engine::init_enemy() {
  SDL_Rect srcClip{0, 0, TEXTURE_SIZE, TEXTURE_SIZE};
  const SDL_Texture *texture_enemy =
      Engine::load_texture("resources/Characters/Player1.png");
  enemies.emplace_back(std::make_unique<Enemy>(texture_enemy, srcClip));
}

void Engine::run() {
  SDL_Log("Engine is running.\n");
  init_stage();
  init_player();
  init_enemy();
  player->set_stage(stage.get());

  while (game_running) {
    while (SDL_PollEvent(&event)) {
      if (event.key.keysym.sym == SDLK_q) {
        SDL_Log("Quitting game.");
        game_running = false;
      }

      Engine::clear();

      render();
      update();

      Engine::display();
    }
  }
}

void Engine::render() {
  for (const auto &t : stage->get_tiles()) {
    Engine::render(*t);
  }
  render(*player);
  for (const auto &e : enemies) {
    render(*e);
  }
}

void Engine::update() {
  player->handle_keypress(event);
  player->update();
  for (const auto &e : enemies) {
    e->update();
  }
}

const SDL_Texture *Engine::load_texture(const char *filepath) {
  if (!filepath) {
    SDL_Log("Cannot load texture. No filepath has been passed in.\n");
  }

  SDL_Texture_ptr tex =
      SDL_Texture_ptr(IMG_LoadTexture(renderer.get(), filepath));

  if (!tex) {
    SDL_Log("Failed to load texture: %s\n", filepath);
  }

  textures.push_back(std::move(tex));
  return textures.back().get();
}

void Engine::clear() { SDL_RenderClear(renderer.get()); }
void Engine::display() const { SDL_RenderPresent(renderer.get()); }

void Engine::render(const Actor &a) const {
  int texture_size = a.get_srcClip().h; // assuming that h == w
  auto [y, x] = a.get_position();
  x *= texture_size;
  y *= texture_size;
  SDL_Rect dst{x, y, texture_size, texture_size};
  Engine::render(const_cast<SDL_Texture *>(a.get_Texture()), a.get_srcClip(),
                 dst);
}

void Engine::render(const Tile &t) const {
  int texture_size = t.get_srcClip().h;
  auto [x, y] = t.get_position();
  x *= texture_size;
  y *= texture_size;
  SDL_Rect dst{x, y, texture_size, texture_size};
  Engine::render(const_cast<SDL_Texture *>(t.get_texture()), t.get_srcClip(),
                 dst);
}

void Engine::render(const SDL_Texture *tex, const SDL_Rect &srcClip,
                    const SDL_Rect &dst) const {
  if (tex == nullptr) {
    SDL_Log("Trying to render nullptr texture.");
  }
  SDL_RenderCopy(renderer.get(), const_cast<SDL_Texture *>(tex), &srcClip,
                 &dst);
}

bool Engine::game_running = true;
uint32_t Engine::start_time = 0;
uint32_t Engine::end_time = 0;
uint32_t Engine::delta_time = 0;
bool Engine::instantiated = false;
