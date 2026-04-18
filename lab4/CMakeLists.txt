cmake_minimum_required(VERSION 4.1)
project(lab4 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab4 main.c
        tree.c
        tree.h
        tests.c)
