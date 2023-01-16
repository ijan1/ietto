#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
 public:
   Player();
   Player(SDL_Texture *texture, SDL_Rect srcClip);
   void handle_keypress(SDL_Event *event);
   void update();
 private:
  int health;
};
#endif /* ifndef PLAYER_HPP */
