#ifndef _randomutils_h
#define _randomutils_h

#include <algorithm>    // std::shuffle
#include <chrono>
#include <random>       // std::default_random_engine

class RandomUtils {
private:
  std::default_random_engine ru_seed;

public:
  RandomUtils() : ru_seed(std::chrono::system_clock::now().time_since_epoch().count()) {}

  template <typename ForwardIt>
  void shuffler(ForwardIt first, ForwardIt last) {
    std::shuffle(first, last, ru_seed);
  }
};

#endif