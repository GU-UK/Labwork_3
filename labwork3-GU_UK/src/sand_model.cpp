#include <iostream>
#include "sand_model.h"

void CreateMatrix(CommandsArguments &case_arg, SizeMatrix &size_matrix, uint64_t **&sandArr) {
    bool stable;
    int iter = 0;
    do {
        stable = true;
        iter += 1;
        bool expandTop = false;
        bool expandBottom = false;
        bool expandLeft = false;
        bool expandRight = false;

        // Проверка на необходимость расширения
        for (int y = 0; y < size_matrix.height; ++y) {
            for (int x = 0; x < size_matrix.width; ++x) {
                if (sandArr[y][x] > 3) {
                    if (y == 0) expandTop = true;
                    if (y == size_matrix.height - 1) expandBottom = true;
                    if (x == 0) expandLeft = true;
                    if (x == size_matrix.width - 1) expandRight = true;
                }
            }
        }

        // Увеличение размера массива
        int new_x_size = size_matrix.width + (expandLeft ? 1 : 0) + (expandRight ? 1 : 0);
        int new_y_size = size_matrix.height + (expandTop ? 1 : 0) + (expandBottom ? 1 : 0);

        // Создание нового массива
        uint64_t **new_sand_Arr = new uint64_t *[new_y_size];
        for (int i = 0; i < new_y_size; ++i) {
            new_sand_Arr[i] = new uint64_t[new_x_size]();
        }
        int down = expandTop ? 1 : 0;
        int right = expandLeft ? 1 : 0;
        for (int y = 0; y < size_matrix.height; ++y) {
            for (int x = 0; x < size_matrix.width; ++x) {
                if (sandArr[y][x] >= 4) {
                    stable = false;
                    uint64_t grains = sandArr[y][x];
                    new_sand_Arr[y + down][x + right] = grains % 4;
                    uint64_t temp = grains / 4;

                    // Рассыпание песка
                    new_sand_Arr[down + y - 1][x + right] += temp;
                    new_sand_Arr[down + y + 1][x + right] += temp;
                    new_sand_Arr[y + down][right + x - 1] += temp;
                    new_sand_Arr[y + down][right + x + 1] += temp;
                } else {
                    new_sand_Arr[y + down][x + right] += sandArr[y][x];
                }
            }
        }

        // Освобождение старого массива
        for (int i = 0; i < size_matrix.height; ++i) {
            delete[] sandArr[i];
        }
        delete[] sandArr;

        // Переключение на новый
        sandArr = new_sand_Arr;
        size_matrix.width = new_x_size;
        size_matrix.height = new_y_size;
        // for (int y=0;y<size_matrix.height;y++){
        //     for (int x=0;x<size_matrix.width;x++){
        //         std::cout << sandArr[y][x] << " ";
        //     }
        //     std::cout <<'\n';
        // }

        if (case_arg.freq && iter % case_arg.freq_count == 0) {
            CreateBMP(case_arg, size_matrix, sandArr, iter);
        }

        if (case_arg.max_iter && case_arg.max_iter_count == iter) {
            break;
        }

    } while (!stable);
    std::cout << iter << '\n';
}
