#include <array>
#include <iostream>
#include <string>
#include <string_view>

#include "enums/CharGroupEnum.h"
#include "PassgenUtils.h"
#include "zxcvbn-c/zxcvbn.h"

//== Some default values.
constexpr size_t default_pass_length{ 7 };

PassgenUtils pu{};

/**
 * @brief Stores options selected by the user.
 *
 * This structure keeps track of the password generation settings such as
 * password length, whether to display password strength, and the 
 * selected character groups.
 */

/// This struct stores the options passed in via CLI.
struct RunningOptions {
  size_t pass_length{ default_pass_length };  //!< Password length.
  bool show_password_strength{ false };
  std::array<bool, GROUPS_AMOUNT> activeGroups{};
  int activeGroupsCounter{ 0 };
};

/**
 * @brief Fuction that shows help to the user. 
 * Shows each one of the groups available
 *
 * It shows a massage of help, the user can see arguments, e the right way of write an input
 * Can be called when there is an error or the user asks for help.
 *
 */

/// Show help screen and error message
void usage(std::string_view msg = "") {
  if (!msg.empty()) {
    std::cerr << msg << "\n\n";
  }

  std::cout << "This program generates passwords of specific length\nbased on the selection of groups of characters.\n\n";

  std::cout << "Usage: passgen [<options>]\n"
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

/**
 * @brief Gets the user input and validates it.
 *
 * Parses the command-line arguments provided by the user and updates
 * the RunningOptions structure. Then validate the argumentsoptions like help,
 * password length, password strength analysis, and active character groups.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param run_options Struct where the parsed options will be stored.
 */



/// Validates and parses the command line arguments
void validate_arguments(int argc, char* argv[], RunningOptions& run_options) {
  bool areAllGroupsArgActive{ false };

  for (size_t i{ 1 }; i < (size_t)argc; ++i) {
    std::string_view currentArg{ argv[i] };

    if (currentArg == "-h" || currentArg == "--help") {
      usage();
      exit(EXIT_SUCCESS);
    } else if (currentArg == "--len") {
      int lengthValue{pu.getLength(argv[i + 1])};
      
      if (lengthValue == 0) {
        usage(">>> ERROR: Invalid value to --len argument");
        exit(EXIT_FAILURE);
      }

      run_options.pass_length = lengthValue;
      i++;
    } else if (currentArg == "-t" || currentArg == "--strength") {
      run_options.show_password_strength = true;
    } else {
      CharGroup validationResult{ pu.getArgGroup(currentArg) };

      if (validationResult == CharGroup::INVALID) {
        std::string errorMsg{">>> ERROR: "};
        errorMsg.append(currentArg);
        errorMsg.append(" is not a valid argument");

        usage(errorMsg);
        exit(EXIT_FAILURE);
      } else if (validationResult == CharGroup::ALL) {
        areAllGroupsArgActive = true;
      }

      run_options.activeGroups[validationResult] = true;
      run_options.activeGroupsCounter++;
    }
  }

  if (run_options.activeGroupsCounter == 0) {
    run_options.activeGroups[CharGroup::LOWER] = true;
    run_options.activeGroupsCounter = 1;
  }

  if (areAllGroupsArgActive) {
    run_options.activeGroups = {true, true, true, true, true, true, true, true, true};
    run_options.activeGroupsCounter = GROUPS_AMOUNT;
  } 

  if (run_options.pass_length < (size_t)run_options.activeGroupsCounter) {
    run_options.pass_length += run_options.activeGroupsCounter - run_options.pass_length;
  }
}

/**
 * @brief Generates a password based on the provided options.
 *
 * Iterates through the active character groups and appends randomly selected characters 
 * to build a password of the desired length. Ensures a balanced distribution of character types.
 * Finally, shuffles the resulting password for added randomness.
 *
 * @param run_options Struct containing the user options for the generation of the password.
 * @return The generated password.
 */


std::string generate_password(const RunningOptions& run_options) {
  std::string password{};
  size_t charsPerGroup{run_options.pass_length / run_options.activeGroupsCounter};

  for (size_t idx { 0 }; idx <= GROUPS_AMOUNT; ++idx) {
    if (password.size() < run_options.pass_length) {
      if (idx == GROUPS_AMOUNT) {
        idx = 0;
        charsPerGroup = (run_options.pass_length - password.size()) / run_options.activeGroupsCounter;

        if (charsPerGroup == 0) charsPerGroup++;
      }
    } else {
      break;
    }

    if (!run_options.activeGroups[idx]) {
      continue;
    }

    password += pu.groupDiceRoller(idx, charsPerGroup);
  }

  pu.shuffler(password.begin(), password.end());
  return password;
}

/**
 * @brief Evaluates the strength of a given password.
 *
 * Calculates the password's entropy using the zxcvbn-c library and 
 * returns a strenght classification of the password.
 *
 * @param password The password to evaluate.
 * @return A string indicating the password's strength.
 */


std::string password_quality(std::string password) {
  double entropy = ZxcvbnMatch(password.c_str(), nullptr, nullptr);

  ZxcvbnUnInit();

  if (entropy < 20) {
    return "Very weak";
  } else if (entropy >= 20 && entropy < 70) {
    return "Weak";
  } else if (entropy >= 70 && entropy < 120) {
    return "Medium";
  } else if (entropy >= 120 && entropy < 160) {
    return "Strong";
  }

  return "Excellent";
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
