#include "Player.hpp"

Player::Player() : health(100) {}
Player::Player(SDL_Texture *texture, SDL_Rect srcClip)
    : Entity(texture, srcClip) {}

void Player::update() {
  ;
  ;
}

void Player::handle_keypress(SDL_Event *e) {
  switch (e->type) {
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym) {
        case SDLK_w:
          coordinates_.second -= 1; // A pair is kinda ugly and
          break;                    // difficult to follow
        case SDLK_s:
          coordinates_.second += 1;
          break;
        case SDLK_d:
          coordinates_.first += 1;
          break;
        case SDLK_a:
          coordinates_.first -= 1;
          break;
      }
  }
}
