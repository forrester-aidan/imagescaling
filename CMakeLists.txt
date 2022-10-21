cmake_minimum_required(VERSION 3.23)
project(scaler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(scaler
        ConsoleGfx.cpp
        ConsoleGfx.h
        Image.cpp
        Image.h
        scaler.cpp)
