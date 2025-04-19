cmake_minimum_required(VERSION 3.10)
project(learningforwork)

add_definitions("-Wall -g")

set(BIN_DIR ${CMAKE_BINARY_DIR}/build/bin)
set(LIB_DIR ${CMAKE_BINARY_DIR}/build/lib)

add_subdirectory(public)
add_subdirectory(ExternalSort)
add_subdirectory(HeapSort)
add_subdirectory(MultiThread)
add_subdirectory(SocketCommunication)
add_subdirectory(SharedMemory)

link_directories(${LIB_DIR})
