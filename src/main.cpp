#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>

//== Some default values.
constexpr size_t default_pass_length{ 7 };

/// This struct stores the options passed in via CLI.
struct RunningOptions {
  size_t pass_length{ default_pass_length };  //!< Password length.
  bool show_password_strength{ false };
  // TODO: Add the groups selected here!
};

/// Show help screen and error message
void usage(std::string_view msg = "") {
  std::cout <<
        "Usage: passgen [<options>]\n"
        " --len n        Size of the password (default is 7).\n"
        "  -l, --lower        Add letter in [a-z].\n"
        "  -u, --upper        Add letter in [A-Z].\n"
        "  -d, --digits       Add letter in [0-9].\n"
        "  -o, --logograms    Add letter in [#$%&@^`~].\n"
        "  -p, --punctuation  Add letter in [.,;:].\n"
        "  -q, --quotes       Add letter in [\\\"\\'].\n"
        "  -s, --slashes      Add letter in [\\/|_-].\n"
        "  -m, --math         Add letter in [*+!?=].\n"
        "  -b, --braces       Add letter in [{}[]()].\n"
        "  -a, --all-groups   Add letter from all the above groups.\n"
        "  -t, --strength     Show password strength classification.\n"
        "  -h, --help         Show this help screen.\n";
}

/// Validates and parses the command line arguments
void validate_arguments(int argc, char* argv[], RunningOptions& run_options) {
  // TODO Add your code here.
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
