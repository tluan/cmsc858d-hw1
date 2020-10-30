cmake_minimum_required(VERSION 3.17)
project(858d)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include_directories("/usr/local/include")
link_directories("/usr/local/lib/")

find_package(boost REQUIRED STATIC)
find_package(divsufsort REQUIRED STATIC)

add_executable(bwt bwt.cpp)
add_executable(assignment1 assignment1.cpp bwocc.cpp)
add_executable(newrank newrank.cpp newrank.h)
add_executable(bws bws.cpp)
add_executable(bwocc bwocc.cpp)

target_link_libraries(bwt divsufsort)
target_link_libraries(bws divsufsort)
target_link_libraries(bwocc divsufsort)
target_link_libraries(newrank divsufsort)