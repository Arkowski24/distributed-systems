cmake_minimum_required(VERSION 3.10)
project(distributed_systems)

set(CMAKE_CXX_STANDARD 14)

add_executable(APP lab1/token/TokenInStream.cpp lab1/token/TokenInStream.h lab1/app.cpp lab1/token/Token.cpp lab1/token/Token.h lab1/token/TokenOutStream.cpp lab1/token/TokenOutStream.h lab1/client/Client.cpp lab1/client/Client.h lab1/client/ThreadSafeQueue.h lab1/system/TokenRingSystem.cpp lab1/system/TokenRingSystem.h lab1/system/Message.h)