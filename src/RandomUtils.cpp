#include <algorithm>    // std::shuffle
#include <chrono>
#include <random>       // std::default_random_engine

#include "RandomUtils.h"

RandomUtils::RandomUtils() 
	: ru_seed(std::chrono::system_clock::now().time_since_epoch().count())
{}

template<typename ForwardIt>
void RandomUtils::shuffler(ForwardIt first, ForwardIt last) {
	std::shuffle(first, last, ru_seed);
}