#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Map.hpp"

enum class PlayerState {
  IDLE, // IDLE
  MOVE_NORTH,
  MOVE_SOUTH,
  MOVE_EAST,
  MOVE_WEST
};

class Player : public Entity {
 public:
  Player();
  Player(const SDL_Texture *texture, SDL_Rect srcClip);
  void handle_keypress(SDL_Event *event);
  void update(Map *map);

 private:
  PlayerState state_;
  int health_;
};
#endif /* ifndef PLAYER_HPP */
