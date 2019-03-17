cmake_minimum_required(VERSION 3.10)
project(token_ring_lib)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(lib)
include_directories(lib/client)
include_directories(lib/client/tcp)
include_directories(lib/client/udp)
include_directories(lib/system)
include_directories(lib/token)

add_library(TOKEN_RING_LIB STATIC
        lib/client/tcp/ClientTCP.cpp
        lib/client/tcp/ClientTCP.h
        lib/client/udp/ClientUDP.cpp
        lib/client/udp/ClientUDP.h
        lib/client/Client.cpp
        lib/client/Client.h
        lib/client/ThreadSafeDeque.h
        lib/system/Message.h
        lib/system/TokenMessageProcessor.cpp
        lib/system/TokenMessageProcessor.h
        lib/system/TokenRingSystem.cpp
        lib/system/TokenRingSystem.h
        lib/system/TokenRingUtility.cpp
        lib/system/TokenRingUtility.h
        lib/token/Token.cpp
        lib/token/Token.h
        lib/token/TokenInStream.cpp
        lib/token/TokenInStream.h
        lib/token/TokenOutStream.cpp
        lib/token/TokenOutStream.h)

add_executable(TEST_APP test/app.cpp)
target_link_libraries(TEST_APP TOKEN_RING_LIB)
target_link_libraries(TEST_APP Threads::Threads)