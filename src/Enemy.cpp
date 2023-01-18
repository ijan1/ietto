#include "Enemy.hpp"

#include <random>

#include "Map.hpp"

Enemy::Enemy(const SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip), state_(EnemyState::IDLE){};

void Enemy::update(Map *map) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 10);

  auto [old_x, old_y] = get_coordinates();
  Tile *current_tile = map->get_tile(old_x, old_y);
  SDL_Log("Currently on tile: %d:%d\n", old_x, old_y);

  int new_x = old_x;
  int new_y = old_y;
  if (distrib(gen) >= 5) {
    new_x += 1;
  } else {
    new_y += 1;
  }

  new_x = std::max(0, new_x);
  new_y = std::max(0, new_y);
  new_x = std::min(new_x, map->max_bound_x());
  new_y = std::min(new_y, map->max_bound_y());

  Tile *tile_target = map->get_tile(new_x, new_y);

  //  if (state_ == EnemyState::WANDERING) {
  if (tile_target->is_walkable()) {
    current_tile->move_enemy_to(tile_target);
    set_coordinates({new_x, new_y});
    SDL_Log("Moved to tile: %d:%d\n", new_x, new_y);
  }
  // }
}
