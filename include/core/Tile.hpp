#ifndef TILE_HPP
#define TILE_HPP

#include "SDL_wrappers.hpp"
#include "core/Actor.hpp"

enum class TileType { FLOOR, WALL, RESERVED };

class Tile {
 public:
  Tile(const SDL_Texture *texture, TileType type, Position pos);

  const Position get_position() const;
  void set_position(Position pos);
  TileType get_tileType() const;
  void set_tileType(TileType type);
  Actor *get_actor() const;
  void set_actor(Actor *actor);

  bool is_walkable() const;
  bool has_actor() const;

  const SDL_Texture *get_texture() const;
  void set_texture(const SDL_Texture *texture);
  SDL_Rect get_srcClip() const;
  void set_srcClip(const SDL_Rect &srcClip);

 private:
  Position position;
  TileType type;
  Actor *actor;

  const SDL_Texture *texture;
  SDL_Rect srcClip;
};

#endif /* TILE_HPP */
