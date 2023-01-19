#ifndef POSITION_HPP
#define POSITION_HPP

#include <assert.h>

#include <array>
#include <compare>

class Position {
 public:
  Position(int x = 0, int y = 0);
  Position operator+(const Position &p);
  Position operator-(const Position &p);
  Position operator*(const Position &p);
  Position operator/(const Position &p);

  // https://devblogs.microsoft.com/cppblog/simplify-your-code-with-rocket-science-c20s-spaceship-operator/
  constexpr bool operator<=>(const Position &p) const = default;

  int x;
  int y;
};

#endif /* ifndef POSITION_HPP */
