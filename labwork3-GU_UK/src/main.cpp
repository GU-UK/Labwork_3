#include <iostream>
#include "parser.h"
#include "bmp.h"            
#include "sand_model.h"     
#include "common.h"    
#include "read_file.h"   


int main(int argc, char **argv)
{
    CommandsArguments case_arg;
    SizeMatrix size_matrix;
    uint64_t **sandArr = nullptr;

    ParseArgument(argc, argv, case_arg);
    ReadTsv(case_arg, size_matrix, sandArr);
    CreateMatrix(case_arg, size_matrix, sandArr);

    case_arg.freq = false;
    CreateBMP(case_arg, size_matrix, sandArr, 0);

    // Освобождение памяти
    for (int i = 0; i < size_matrix.height; ++i) {
        delete[] sandArr[i];
    }
    delete[] sandArr;

    return 0;
}
