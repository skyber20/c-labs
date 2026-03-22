cmake_minimum_required(VERSION 4.1)
project(lab3 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab3 main.c
        logic.c
        structures.c
        parse_expr.c
        stack.c
        rpn.c
        tree.c)
