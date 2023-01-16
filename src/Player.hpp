#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Tile.hpp"

enum class Direction {
  IDLE, // IDLE
  NORTH,
  SOUTH,
  EAST,
  WEST
};

class Player : public Entity {
 public:
  Player();
  Player(SDL_Texture *texture, SDL_Rect srcClip);
  void handle_keypress(SDL_Event *event);
  void update(std::vector<Entity *> &world);

 private:
  Direction direction_;
  int health;
};
#endif /* ifndef PLAYER_HPP */
