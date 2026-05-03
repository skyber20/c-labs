cmake_minimum_required(VERSION 4.1)
project(lab5 C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab5
        main.c
        graph.h
        graph.c
        dijkstra.h
        dijkstra.c
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

set(BENCHMARK_ENABLE_TESTING OFF)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_Declare(
        googlebenchmark
        URL https://github.com/google/benchmark/archive/refs/tags/v1.9.5.zip
)
FetchContent_MakeAvailable(googlebenchmark)

enable_testing()

add_executable(lab5_tests
        tests.cpp
        graph.c
        dijkstra.c
)

target_link_libraries(lab5_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab5_tests)

add_executable(lab5_bench
        benchmark.cpp
        graph.c
        dijkstra.c
)

target_link_libraries(lab5_bench benchmark::benchmark)
