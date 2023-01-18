#include "Enemy.hpp"

#include <random>

#include "Map.hpp"

Enemy::Enemy() : state_(EnemyState::IDLE), health_(100) {}
Enemy::Enemy(const SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip), state_(EnemyState::IDLE){};

void Enemy::update(Map *map) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 10);

  int old_x = get_x_pos();
  int old_y = get_y_pos();
  Tile *current_tile = map->get_tile(old_x, old_y);
  SDL_Log("Currently on tile: %d:%d\n", old_x, old_y);

  int new_x = old_x;
  int new_y = old_y;
  // if (distrib(gen) >= 5) {
  new_x += 1;
  //} else {
  new_y += 1;
  //}

  if (new_x < 0) new_x = 0;
  if (new_y < 0) new_y = 0;
  if (new_x >= 29) new_x = 29;
  if (new_y >= 39) new_x = 39;

  Tile *tile_target = map->get_tile(new_x, new_y);

  //  if (state_ == EnemyState::WANDERING) {
  if (tile_target->is_walkable()) {
    current_tile->move_enemy_to(tile_target);
    set_coordinates(new_y, new_x);
    SDL_Log("Moved to tile: %d:%d\n", new_x, new_y);
  }
  // }
}
