#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include "common.h"

// Функция для чтения TSV файла и заполнения массива песка
void ReadTsv(CommandsArguments &case_arg, SizeMatrix &size_matrix, uint64_t **&sandArr)
{
    std::ifstream file(case_arg.name_tvs_file);
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << case_arg.name_tvs_file << '\n';
        return;
    }
    // высчитываем размеры матрицы
    size_matrix.width = 0;
    size_matrix.height = 0;
    int len_x, len_y, temp;
    int len_x_max = 0, len_y_max = 0, len_x_min = 0, len_y_min = 0;

    while (file >> len_x >> len_y >> temp)
    {
        
        len_x_max = std::max(len_x_max, len_x);
        len_y_max = std::max(len_y_max, len_y);
        len_x_min = std::min(len_x_min, len_x);
        len_y_min = std::min(len_y_min, len_y);
    }
    size_matrix.width = len_x_max + abs(len_x_min) + 1;
    size_matrix.height = len_y_max + abs(len_y_min) + 1;

    // Создаем массив
    sandArr = new uint64_t *[size_matrix.height];
    for (int i = 0; i < size_matrix.height; ++i)
    {
        sandArr[i] = new uint64_t[size_matrix.width]();
    }

    // Заполнение массива
    file.clear();  // Сбрасываем состояние файла
    file.seekg(0); // Возвращаемся в начало файла
    int mid_x = abs(len_x_min);
    int mid_y = len_y_max;
    while (file >> len_x >> len_y >> temp)
    {
        sandArr[mid_y - len_y][mid_x + len_x] = temp;
    }
    file.close();
}
