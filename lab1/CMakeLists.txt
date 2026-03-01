cmake_minimum_required(VERSION 4.1)
project(lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab1 tree.c
        tests.c
        main.c)