#ifndef GROUPS_AMOUNT
#define GROUPS_AMOUNT 9
#endif

#ifndef _chargoupenum_h
#define _chargoupenum_h

#include <cstdint>

enum CharGroup : std::uint8_t {
  LOWER = 0,    //!< a-z
  UPPER,        //!< A-Z
  DIGITS,       //!< 0-9
  LOGOGRAMS,    //!< # $ % \* @ ^ ` ~
  PUNCTUATION,  //!< . , ; :
  QUOTES,       //!< " '
  SLASHES,      //!< \ / | \_ -
  MATH,         //!< < > \* + ! ? =
  BRACES,       //!< } { ] [ ) (
  ALL,          //!< All groups above.
  INVALID,      //!< Invalid group.
};
#endif