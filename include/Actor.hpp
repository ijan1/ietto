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
  void set_position(const Position &position);

  virtual void update() = 0;

  const SDL_Texture *get_Texture() const;
  void set_Texture(SDL_Texture *texture);
  const SDL_Rect get_srcClip() const;
  void set_srcClip(const SDL_Rect &srcClip);

 private:
  int health;
  int maxHealth;
  Position position;

  static Map *stage;

  const SDL_Texture *texture;
  SDL_Rect srcClip;
};

#endif /* ACTOR_HPP */
