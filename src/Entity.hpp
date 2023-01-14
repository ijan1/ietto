#include "SDL.h"
#include "SDL_image.h"

class Entity {
  public:
    Entity(double x, double y, SDL_Texture *texture);
    void update(SDL_Event &event);
    inline SDL_Rect *get_frame() {return &currentFrame;};
  private:
    int x,y;
    const int speed = 16;
    SDL_Rect currentFrame;
    SDL_Texture *texture;
};
