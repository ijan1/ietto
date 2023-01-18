#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Actor.hpp"
#include "Map.hpp"

enum class Direction {
  IDLE = 0,
  MOVE_NORTH = 1,
  MOVE_SOUTH = 2,
  MOVE_EAST = 4,
  MOVE_WEST = 8,
  MOVE_NORTHEAST = MOVE_NORTH | MOVE_EAST,
  MOVE_NORTHWEST = MOVE_NORTH | MOVE_WEST,
  MOVE_SOUTHEAST = MOVE_SOUTH | MOVE_EAST,
  MOVE_SOUTHWEST = MOVE_SOUTH | MOVE_WEST
};

inline constexpr Direction operator|(Direction x, Direction y) {
  return static_cast<Direction>(static_cast<int>(x) | static_cast<int>(y));
}

class Player : public Actor {
 public:
  Player(const SDL_Texture *texture, const SDL_Rect &srcClip);
  ~Player() override;

  void set_stage(Map *stage);
  void handle_keypress(SDL_Event &e);
  void update() override;

 private:
  Map *stage;
  Direction direction;
};

#endif /* PLAYER_HPP */
