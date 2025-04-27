#ifndef _passgenutils_h
#define _passgenutils_h

#include <algorithm>  // std::shuffle
#include <array>
#include <chrono>
#include <random>  // std::default_random_engine
#include <string_view>
#include <unordered_map>

#include <iostream>

#include "enums/CharGroupEnum.h"

class PassgenUtils {
private:
public:
  PassgenUtils() {}

  template <typename ForwardIt>
  void shuffler(ForwardIt first, ForwardIt last) {
    auto seed{ std::chrono::system_clock::now().time_since_epoch().count() };
    std::shuffle(first, last, std::default_random_engine(seed));
  }

  CharGroup getArgGroup(std::string_view arg) {
    static std::unordered_map<std::string_view, CharGroup> validArgs{
      { "-l", CharGroup::LOWER },       { "--lower", CharGroup::LOWER },
      { "-u", CharGroup::UPPER },       { "--upper", CharGroup::UPPER },
      { "-d", CharGroup::DIGITS },      { "--digits", CharGroup::DIGITS },
      { "-o", CharGroup::LOGOGRAMS },   { "--logograms", CharGroup::LOGOGRAMS },
      { "-p", CharGroup::PUNCTUATION }, { "--punctuation", CharGroup::PUNCTUATION },
      { "-q", CharGroup::QUOTES },      { "--quotes", CharGroup::QUOTES },
      { "-s", CharGroup::SLASHES },     { "--slashes", CharGroup::SLASHES },
      { "-m", CharGroup::MATH },        { "--math", CharGroup::MATH },
      { "-b", CharGroup::BRACES },      { "--braces", CharGroup::BRACES },
      { "-a", CharGroup::ALL },         { "--all-groups", CharGroup::ALL }
    };

    auto it = validArgs.find(arg);
    if (it != validArgs.end()) {
      return it->second;
    }

    return CharGroup::INVALID;
  }

  std::string groupDiceRoller(size_t charGroupIdx, size_t n) {
    static std::array<size_t, GROUPS_AMOUNT> charGroupsOffset;
    static std::array<std::string_view, GROUPS_AMOUNT> charGroups = {
      "abcdefghijklmnopqrstuvwxyz",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "0123456789",
      "#$%&@^`~",
      ".,;:",
      "\"\'",
      "\\/|_-",
      "<>*+!?=",
      "}{][)(",
    };

    if (charGroupsOffset[charGroupIdx] >= charGroups[charGroupIdx].size()) {
      charGroupsOffset[charGroupIdx] = 0;
    }

    std::string currentGroup{charGroups[charGroupIdx]};

    shuffler(currentGroup.begin(), currentGroup.end());

    std::string chars{currentGroup.substr(charGroupsOffset[charGroupIdx], n) };
    charGroupsOffset[charGroupIdx] += n;

    return chars;
  }

  int getLength(const char lengthArg[]) {
    if (lengthArg == NULL) {
      return 0;
    }

    int lenthValue{ atoi(lengthArg) };

    if (lenthValue <= 0) {
      return 0;
    }

    return lenthValue;
  }
};

#endif