#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Position.hpp"
#include "SDL_wrappers.hpp"

class Map;

class Actor {
 public:
  Actor(const SDL_Texture *texture, const SDL_Rect &srcClip);
  virtual ~Actor() = 0;

  int get_current_health() const;
  void set_current_health(const int health);
  int get_max_health() const;
  void set_max_health(const int maxHealth);
  const Position get_position() const;
  void set_position(const Position position);
  // Tile *get_current_tile() const;

  bool can_move_to(const Position pos);
  void move_to(const Position pos);

  Map *get_stage() const;
  void set_stage(Map *stage);

  virtual void update() = 0;

  const SDL_Texture *get_Texture() const;
  void set_Texture(SDL_Texture *texture);
  const SDL_Rect get_srcClip() const;
  void set_srcClip(const SDL_Rect &srcClip);

 private:
  int health;
  int maxHealth;
  Position position;

  // All actors have access to the stage they're in
  static Map *stage;

  const SDL_Texture *texture;
  SDL_Rect srcClip;
};

#endif /* ACTOR_HPP */
