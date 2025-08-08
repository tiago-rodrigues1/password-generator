# Password Generator

This project implements a command-line password generator called `passgen`, written in C++. It produces secure, random passwords of customizable length and complexity, based on user-selected groups of characters.

## Features

- **Customizable password length** (`--len n`, default is 7)
- **Character groups:** Lowercase, uppercase, digits, logograms, punctuation, quotes, slashes, math symbols, and braces
- **At least one character from each selected group** (or all groups with `--all-groups`)
- **Password strength evaluation** (with `--strength` or `-t`), classified into categories from _Very Weak_ to _Excellent_
- **Command-line interface (CLI)** with help screen (`--help`)
- **Error handling** for input and argument validation

## Character Groups

| Group         | Characters                       |
|---------------|----------------------------------|
| lower         | a-z                              |
| upper         | A-Z                              |
| digits        | 0-9                              |
| logograms     | # $ % & @ ^ ` ~                  |
| punctuation   | . , ; :                          |
| quotes        | " '                              |
| slashes       | \ / | _ -                        |
| math          | < > * + ! ? =                    |
| braces        | } { ] [ ) (                      |

## Usage

Basic examples:
```bash
./passgen --len 10 --lower --upper
# Output: LbgvcaQTPE

./passgen --len 20 --all-groups -t
# Output: sV"!>`.C{0[1':(/L@?  >>> Password strength: Excellent
```

Available options:
```
--len n        Size of the password (default is 7)
-l, --lower        Add lowercase letters [a-z]
-u, --upper        Add uppercase letters [A-Z]
-d, --digits       Add digits [0-9]
-o, --logograms    Add logogram characters [#$%&@^`~]
-p, --punctuation  Add punctuation [.,;:]
-q, --quotes       Add quotes ["']
-s, --slashes      Add slashes [\/|_-]
-m, --math         Add math symbols [*+!?=]
-b, --braces       Add braces [{}[]()]
-a, --all-groups   Add all character groups
-t, --strength     Show password strength classification
-h, --help         Show help screen
```

If no group is chosen, only lowercase letters are used.

## Password Strength

Quality is classified in five categories based on length, diversity, and repetition:
- _Very Weak_: 1–3 chars, minimal diversity
- _Weak_: up to 5 chars, only one group
- _Medium_: 5+ chars, 2–3 groups
- _Strong_: 10+ chars, 4+ groups, no repetition
- _Very Strong_: 15+ chars, 6+ groups, no repetition
- _Excellent_: 25+ chars, all groups, few repeats

## Implementation Notes

- Ensures one character from each selected group
- Shuffles password for randomness
- Validates arguments and handles errors
- Code organized using `struct` and functions for clarity
