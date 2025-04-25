#ifndef _argvalidator_h
#define _argvalidator_h

#include <string>
#include "../include/enums/CharGroupEnum.h"
#include <unordered_map>

class ArgValidator {
private:
  std::unordered_map<std::string, CharGroup> validArgs
    = { { "-l", CharGroup::LOWER },       { "--lower", CharGroup::LOWER },
        { "-u", CharGroup::UPPER },       { "--upper", CharGroup::UPPER },
        { "-d", CharGroup::DIGITS },      { "--digits", CharGroup::DIGITS },
        { "-o", CharGroup::LOGOGRAMS },   { "--logograms", CharGroup::LOGOGRAMS },
        { "-p", CharGroup::PUNCTUATION }, { "--punctuation", CharGroup::PUNCTUATION },
        { "-q", CharGroup::QUOTES },      { "--quotes", CharGroup::QUOTES },
        { "-s", CharGroup::SLASHES },     { "--slashes", CharGroup::SLASHES },
        { "-m", CharGroup::MATH },        { "--math", CharGroup::MATH },
        { "-b", CharGroup::BRACES },      { "--braces", CharGroup::BRACES },
        { "-a", CharGroup::BRACES },      { "--all-groups", CharGroup::ALL } };

public:
  CharGroup validateArg(std::string arg) {
    auto it = validArgs.find(arg);
    if (it != validArgs.end()) {
      return it->second;
    } else {
      return CharGroup::INVALID;
    }
  }
};
#endif
