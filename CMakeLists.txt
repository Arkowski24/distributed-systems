cmake_minimum_required(VERSION 3.10)
project(distributed_systems)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(APP lab1/token/TokenInStream.cpp lab1/token/TokenInStream.h lab1/app.cpp lab1/token/Token.cpp lab1/token/Token.h lab1/token/TokenOutStream.cpp lab1/token/TokenOutStream.h lab1/client/udp/ClientUDP.cpp lab1/client/udp/ClientUDP.h lab1/client/ThreadSafeDeque.h lab1/system/TokenRingSystem.cpp lab1/system/TokenRingSystem.h lab1/system/Message.h lab1/system/TokenRingUtility.cpp lab1/system/TokenRingUtility.h lab1/system/TokenMessageProcessor.cpp lab1/system/TokenMessageProcessor.h lab1/client/tcp/ClientTCP.cpp lab1/client/tcp/ClientTCP.h lab1/client/Client.cpp lab1/client/Client.h)
target_link_libraries(APP Threads::Threads)