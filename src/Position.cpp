#include "Position.hpp"

// TODO: consider swapping so that I can think of
// the position as a Point
Position::Position(int x_, int y_) : x(x_), y(y_) {}

Position Position::operator+(const Position &p) {
  return Position(x + p.x, y + p.y);
}

Position Position::operator-(const Position &p) {
  return Position(x - p.x, y - p.y);
}

Position Position::operator*(const Position &p) {
  return Position(x * p.x, y * p.y);
}

Position Position::operator/(const Position &p) {
  return Position(x / p.x, y / p.y);
}
