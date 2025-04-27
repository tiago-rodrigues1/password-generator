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

/// This struct stores the options passed in via CLI.
struct RunningOptions {
  size_t pass_length{ default_pass_length };  //!< Password length.
  bool show_password_strength{ false };
  std::array<bool, GROUPS_AMOUNT> activeGroups{};
  int activeGroupsCounter{ 0 };
};

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

std::string password_quality(std::string_view password) {
  // TODO Add your code here
  //retorna a qualidade da senha atraves de uma função da lib zxcvbn
  zxcvbn_match_t result = zxcvbn_match(password.data());
  
  switch (result.score){
    std::cout >> "The quality of your password is: ";
        case 0: 
          return "Very weak";

        case 1:
          return "Weak";
        
        case 2:
          return "Medium ";

        case 3:
          return "Good";  

        case 4:
          return "Excellent";
  }
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
