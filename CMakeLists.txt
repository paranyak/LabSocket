cmake_minimum_required(VERSION 3.6)
project(Socket)

set(CMAKE_CXX_STANDARD 14)

#set(SOURCE_FILES client.cpp)
set(SOURCE_FILES server.cpp)
add_executable(Socket ${SOURCE_FILES})