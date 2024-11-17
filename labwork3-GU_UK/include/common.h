#pragma once

struct CommandsArguments {
    char *name_tvs_file;
    char *name_output_file;
    bool max_iter = false;
    int max_iter_count = 10;
    bool freq = false;
    int freq_count = 1;
};

struct SizeMatrix {
    int width = 0;
    int height = 0;
};

