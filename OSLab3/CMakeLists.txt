# CMakeList.txt: проект CMake для OSLab3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
project(OSLab3)

# Добавьте источник в исполняемый файл этого проекта.
set(CMAKE_CXX_STANDARD 98)
add_executable (OSLab3 "OSLab3.cpp" "OSLab3.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
