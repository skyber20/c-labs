cmake_minimum_required(VERSION 4.1)
project(lab2 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab2 logic.c
        main.c
        tests.c)
