#include <chrono>
#include <random>

#include "core/Actor.hpp"

// Taken from https://github.com/CleverRaven/Cataclysm-DDA/blob/master/src/rng.cpp
inline std::default_random_engine &rng_get_engine() {
  static std::default_random_engine eng(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  return eng;
}

// Taken from https://github.com/CleverRaven/Cataclysm-DDA/blob/master/src/rng.cpp
inline int rng(int lo, int hi) {
  static std::uniform_int_distribution<int> rng_int_dist;
  if (lo > hi) {
    std::swap(lo, hi);
  }
  return rng_int_dist(rng_get_engine(),
                      std::uniform_int_distribution<>::param_type(lo, hi));
}

// Taken from https://github.com/CleverRaven/Cataclysm-DDA/blob/master/src/rng.cpp
inline int dice_roll(int number, int sides) {
  int ret = 0;
  for (int i = 0; i < number; i++) {
    ret += rng(1, sides);
  }
  return ret;
}

inline void attack(const Actor &attacker, Actor &defender) {
  int defender_health = defender.get_current_health();
  int damage = dice_roll(1,6);
  defender_health -= damage;
  defender.set_current_health(defender_health);
  SDL_Log("%s attacked %s for %d points of damage!\n", attacker.get_name().data(), defender.get_name().data(), damage);
}
