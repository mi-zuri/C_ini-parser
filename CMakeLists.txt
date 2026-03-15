cmake_minimum_required(VERSION 3.26)
project(CALLP_ini_parser C)

set(CMAKE_C_STANDARD 11)

add_executable(CALLP_ini_parser main.c list.c section.c parser.c errors.c search.c)
