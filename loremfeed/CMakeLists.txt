cmake_minimum_required(VERSION 3.9)

project(loremfeed)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(LoremTest LoremTest.cc LoremFeed.h)

