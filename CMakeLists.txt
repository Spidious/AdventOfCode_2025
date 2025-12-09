cmake_minimum_required(VERSION 4.0)
project(aoc25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")


option(AOC_CHAL "Which AoC Challenge to Build" "template")

add_subdirectory(src)