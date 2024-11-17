#include <iostream>
#include <fstream>
#include <cstdint>
#include "common.h"

void CreateBMP(CommandsArguments &case_arg, SizeMatrix &size_matrix, uint64_t **&array, int iter);
void CreatePath(CommandsArguments &case_arg, int number, char *file, bool freq);
int SizeBufferForPath(CommandsArguments &case_arg, int number);
