#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <array>

#include "../include/enums/CharGroupEnum.h"
#include "../include/ArgValidator.h"

//== Some default values.
constexpr size_t default_pass_length{ 7 };

/// This struct stores the options passed in via CLI.
struct RunningOptions {
  size_t pass_length{ default_pass_length };  //!< Password length.
  bool show_password_strength{ false };
  std::array<bool, GROUPS_AMOUNT> activeGroups{};
};

/// Show help screen and error message
void usage(std::string_view msg = "") {}

/// Validates and parses the command line arguments
void validate_arguments(int argc, char* argv[], RunningOptions& run_options) {
  for (size_t i{0}; i < (size_t)argc; i++) {
    if (argv[i] == "-h" || argv[i] == "--help") {
     //TODO: print usage() 
    } else if (argv[i] == "--len") {
      int lengthValue{atoi(argv[i + 1])};
      //validate length

      run_options.pass_length = lengthValue;
    } else if (argv[i] == "-t" || argv[i] == "--strength") {
      //TODO: call password_quality()
    } else {
      //TODO: validate if arg is valid
      ArgValidator validator{};
      CharGroup result{validator.validateArg(argv[i])};

      if (result == CharGroup::INVALID) {
        //TODO: mostra erro
      }

      run_options.activeGroups[result] = 1;
      
    }
  }
}

std::string generate_password(const RunningOptions& run_options) {
  // TODO Add your code here.
  std::string password;

  return password;
}

std::string password_quality(std::string_view password) {
  // TODO Add your code here
  return "Weak";
}

int main(int argc, char* argv[]) {
  RunningOptions run_options;  // Stores incoming arguments.

  // (1) Validate command line arguments.
  std::cout << "Welcome to passgen v 1.0, © DIMAp 2025\n\n";
  validate_arguments(argc, argv, run_options);
  // (2) Generate password.
  auto password = generate_password(run_options);
  std::cout << ">>> The generated password is:\n" << password << "\n\n";
  // (3) Show password quality if requested.
  if (run_options.show_password_strength) {
    std::cout << ">>> Password strength: " << password_quality(password) << "\n\n";
  }

  return EXIT_SUCCESS;
}
