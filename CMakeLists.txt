project(MathModeling LANGUAGES CXX)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_SOURSE_DIR src/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURSE_DIR})
aux_source_directory(${CMAKE_SOURSE_DIR} SOURSES)
add_executable(${PROJECT_NAME}  ${SOURSES})
