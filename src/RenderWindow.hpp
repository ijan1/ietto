#include "SDL.h"
#include "SDL_image.h"

class RenderWindow {
 public:
  RenderWindow(const char *window_name, int width, int height);
  SDL_Texture *loadTexture(const char *file_path);
  void clear();
  void render(SDL_Texture *texture);
  void render(SDL_Texture *texture, SDL_Rect *clip, SDL_Rect *renderQuad);
  void display();
  void destroy();

 private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};
