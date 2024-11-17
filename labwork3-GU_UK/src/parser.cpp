#include <iostream>
#include <cstring>
#include "parser.h"
#include "common.h"

void ParseArgument(int argc, char **argv, CommandsArguments &case_arg) {
    for (int y = 1; y < argc; y++) {
        char *argument = argv[y];
        char *next_argument = nullptr;
        if (y + 1 < argc) {
            next_argument = argv[y + 1];
        }

        if (strcmp(argument, "--input") == 0 || strcmp(argument, "-y") == 0) {
            case_arg.name_tvs_file = next_argument;
        } else if (strcmp(argument, "--output") == 0 || strcmp(argument, "-o") == 0) {
            case_arg.name_output_file = next_argument;
        } else if (strcmp(argument, "--max-iter") == 0 || strcmp(argument, "-m") == 0) {
            case_arg.max_iter = true;
            case_arg.max_iter_count = std::stoi(next_argument);
        } else if (strcmp(argument, "--freq") == 0 || strcmp(argument, "-f") == 0) {
            case_arg.freq = true;
            case_arg.freq_count = std::stoi(next_argument);
        }
    }
}
