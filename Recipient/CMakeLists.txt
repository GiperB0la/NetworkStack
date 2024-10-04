cmake_minimum_required(VERSION 3.10)
project(Recipient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    include
)

add_executable(Recipient
    src/Main.cpp
    src/Raw_Socket.cpp
)

target_link_libraries(Recipient PRIVATE pthread)