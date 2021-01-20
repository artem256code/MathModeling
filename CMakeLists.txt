cmake_minimum_required(VERSION 3.5)

project(MathModeling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MathModeling
    src/fraction.cpp
    src/fraction.hpp
    src/io.cpp
    src/io.hpp
    src/main.cpp
    src/model.cpp
    src/model.hpp
    tests/tests.cpp
    tests/tests.hpp
    )

