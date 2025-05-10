cmake_minimum_required(VERSION 3.27)
project(Bowling_Scorer C)

set(CMAKE_C_STANDARD 99)

add_executable(Bowling_Scorer main.c test_cases.c Unity-2.6.1/src/unity.c)
