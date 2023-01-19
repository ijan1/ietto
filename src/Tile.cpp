#include "Tile.hpp"

Tile::Tile(const SDL_Texture *tex, TileType type_, Position pos)
    : position(pos),
      type(type_),
      actor(nullptr),
      texture(tex),
      srcClip{0, 0, 16, 16} {}

const Position Tile::get_position() const { return position; }

void Tile::set_position(Position pos) { position = pos; }

TileType Tile::get_tileType() const { return type; }

void Tile::set_tileType(TileType t) { type = t; }

Actor *Tile::get_actor() const { return actor; }

void Tile::set_actor(Actor *a) { actor = a; }

bool Tile::is_walkable() const {
  if (Tile::has_actor()) {
    return false;
  }

  if (type != TileType::FLOOR) {
    return false;
  }

  return true;
}

bool Tile::has_actor() const {
  if (actor) {
    return true;
  }

  return false;
}

void Tile::set_texture(const SDL_Texture *texture_) { texture = texture_; }

const SDL_Texture *Tile::get_texture() const { return texture; }

SDL_Rect Tile::get_srcClip() const { return srcClip; }

void Tile::set_srcClip(const SDL_Rect &srcClip_) { srcClip = srcClip_; }
