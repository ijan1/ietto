#include "Entity.hpp"

Entity::Entity(double x_, double y_, SDL_Texture *tex)
    : x(x_), y(y_), texture(tex){
      currentFrame.x = 0;
      currentFrame.y = 0;
      currentFrame.w = 32;
      currentFrame.h = 32;
    };

void Entity::update(SDL_Event &e) {
  if (e.key.keysym.sym == SDLK_a) {
    currentFrame.x -= speed;
  } else if (e.key.keysym.sym == SDLK_d) {
    currentFrame.x += speed;
  } else if (e.key.keysym.sym ==  SDLK_w) {
    currentFrame.y -= speed;
  } else if (e.key.keysym.sym == SDLK_s) {
    currentFrame.y += speed;
  }
}
