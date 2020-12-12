cmake_minimum_required(VERSION 3.5)

project(MathModeling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MathModeling
    src/fraction.cpp
    src/main.cpp
    src/model.cpp
    tests/tests.cpp
    )

