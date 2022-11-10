cmake_minimum_required(VERSION 3.23)
project(NameGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(NameGenerator main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/names.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
