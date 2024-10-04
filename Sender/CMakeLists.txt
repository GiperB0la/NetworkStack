cmake_minimum_required(VERSION 3.10)
project(Sender)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    include
)

add_executable(Sender
    src/Main.cpp
    src/Raw_Socket.cpp
    src/Protocol_UDP.cpp
    src/Protocol_IP.cpp
)

target_link_libraries(Sender PRIVATE pthread)