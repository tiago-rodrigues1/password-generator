#include <iostream>
#include <iomanip>

//valida os erros e coloca  a msg de ajuda
void usage(){
    std::cout <<
        "Usage: passgen [<options>]\n"
        " --len n        Size of the password (default is 7).\n"
        "-l, --lower        Add letter in [a-z].\n"
        "-u, --upper        Add letter in [A-Z].\n"
        "-d, --digits       Add letter in [0-9].\n"
        "-o, --logograms    Add letter in [#$%&@^`~].\n"
        "-p, --punctuation  Add letter in [.,;:].\n"
        "-q, --quotes       Add letter in [\\\"\\'].\n"
        "-s, --slashes      Add letter in [\\/|_-].\n"
        "-m, --math         Add letter in [*+!?=].\n"
        "-b, --braces       Add letter in [{}[]()].\n"
        "-a, --all-groups   Add letter from all the above groups.\n"
        "-t, --strength     Show password strength classification.\n"
        "-h, --help         Show this help screen.\n";}

int main(int argc, char *argv[]){
    for(size_t ct{ 0 }; ct<(size_t)argc; ++ct){
        std::cout << ">> Arg[" << ct << "] = " << std::quoted(argv[ct]) << "\n";
    }
    return 0;
}


