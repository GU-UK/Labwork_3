#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include "bmp.h"

// Массив цветов для отображения песка
const unsigned char COLORS[4][3] = {
    {255, 255, 255}, // 0 - белый
    {0, 255, 0},     // 1 - зеленый
    {128, 0, 128},   // 2 - фиолетовый
    {0, 255, 255}    // 3 - желтый
};


// Функция для вычисления размера буфера пути
int SizeBufferForPath(CommandsArguments &case_arg, int number) {
    size_t path_len = strlen(case_arg.name_output_file);  // Длина пути
    size_t number_len = 0; // Длина числа

    if (number == 0) {
        number_len = 1;
    } else {
        int temp = number;
        while (temp != 0) {
            temp /= 10;
            number_len++;
        }
    }
    size_t extension_len = 4;
    size_t size = path_len + number_len + extension_len + 2;
    return size;
}


// Функция для создания пути к файлу
void CreatePath(CommandsArguments &case_arg, int number, char *file, bool freq) {
    strcpy(file, case_arg.name_output_file);
    strcat(file, "\\");

    if (freq) {
        char number_str[20];
        sprintf(number_str, "%d", number);
        strcat(file, number_str);
        strcat(file, ".bmp");
    } else {
        strcat(file, "result");
        strcat(file, ".bmp");
    }
}


// Функция для создания BMP-файла
void CreateBMP(CommandsArguments &case_arg, SizeMatrix &size_matrix, uint64_t **&array, int iter) {
    int size_buffer = SizeBufferForPath(case_arg, 1) + 7;
    if (case_arg.freq) {
        size_buffer = SizeBufferForPath(case_arg, iter);
    }
    char file[size_buffer];
    CreatePath(case_arg, iter, file, case_arg.freq);

    std::ofstream bmpFile(file, std::ios::binary);
    const int WIDTH = size_matrix.width;
    const int HEIGHT = size_matrix.height;

    // Заголовок BMP
    unsigned char header[54] = {
        'B', 'M',   // Signature
        0, 0, 0, 0, // File size
        0, 0, 0, 0, // Reserved
        54, 0, 0, 0, // Offset to pixel data
        40, 0, 0, 0, // DIB header size
        (unsigned char)(WIDTH & 0xFF), (unsigned char)((WIDTH >> 8) & 0xFF),
        (unsigned char)((WIDTH >> 16) & 0xFF), (unsigned char)((WIDTH >> 24) & 0xFF),
        (unsigned char)(HEIGHT & 0xFF), (unsigned char)((HEIGHT >> 8) & 0xFF),
        (unsigned char)((HEIGHT >> 16) & 0xFF), (unsigned char)((HEIGHT >> 24) & 0xFF),
        1, 0,    // Color planes
        24, 0,   // Bits per pixel
        0, 0, 0, 0,
        0, 0, 0, 0,
        0x13, 0x0B, 0, 0, // Resolution
        0x13, 0x0B, 0, 0,
        0, 0, 0, 0
    };

    int fileSize = 54 + (3 * WIDTH * HEIGHT);
    header[2] = (unsigned char)(fileSize & 0xFF);
    header[3] = (unsigned char)((fileSize >> 8) & 0xFF);
    header[4] = (unsigned char)((fileSize >> 16) & 0xFF);
    header[5] = (unsigned char)((fileSize >> 24) & 0xFF);

    bmpFile.write(reinterpret_cast<char *>(header), sizeof(header));

    for (int y = HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < WIDTH; ++x) {
            int colorIndex = array[y][x];
            unsigned char r = 0, g = 0, b = 0;

            if (colorIndex >= 0 && colorIndex <= 3) {
                r = COLORS[colorIndex][2];
                g = COLORS[colorIndex][1];
                b = COLORS[colorIndex][0];
            }

            bmpFile.write(reinterpret_cast<char *>(&b), 1);
            bmpFile.write(reinterpret_cast<char *>(&g), 1);
            bmpFile.write(reinterpret_cast<char *>(&r), 1);
        }

        // Дополнительное выравнивание по 4 байта
        for (int i = 0; i < (4 - (WIDTH * 3) % 4) % 4; i++) {
            unsigned char padding = 0;
            bmpFile.write(reinterpret_cast<char *>(&padding), 1);
        }
    }

    bmpFile.close();
}
