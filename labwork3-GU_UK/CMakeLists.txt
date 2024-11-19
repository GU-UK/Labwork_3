cmake_minimum_required(VERSION 3.10)

project(SandSimulation)

set(CMAKE_CXX_STANDARD 17)

# Указываем директорию для заголовочных файлов
include_directories(include)

# Исходники
set(SOURCE_FILES
    src/main.cpp
    src/bmp.cpp
    src/parser.cpp
    src/read_file.cpp
    src/sand_model.cpp
)

# Указываем путь для исполнимого файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Создаем исполнимый файл
add_executable(sand_simulation ${SOURCE_FILES})

# ."C:/Users/ZAERG/Desktop/C++/labwork3-GU_UK/bin/sand_simulation.exe" --input C:\Users\ZAERG\Desktop\C++\TMP\Sand.tsv --output C:\Users\ZAERG\Desktop\C++\TMP\BMP
