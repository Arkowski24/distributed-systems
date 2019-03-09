cmake_minimum_required(VERSION 3.10)
project(distributed_systems)

set(CMAKE_CXX_STANDARD 14)

add_executable(APP lab1/TokenInStream.cpp lab1/TokenInStream.h lab1/app.cpp lab1/Token.cpp lab1/Token.h lab1/TokenOutStream.cpp lab1/TokenOutStream.h)