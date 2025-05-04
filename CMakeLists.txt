cmake_minimum_required(VERSION 3.10)
project(computer_club)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы проекта
set(SOURCES
    src/computer_club.cpp
    src/software.cpp
)

# Создаем исполняемый файл
add_executable(computer_club ${SOURCES})

# Включаем директорию с заголовочными файлами
target_include_directories(computer_club PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Опции для компилятора
if(MSVC)
    target_compile_options(computer_club PRIVATE /W4 /WX)
else()
    target_compile_options(computer_club PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
