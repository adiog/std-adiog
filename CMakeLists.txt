cmake_minimum_required(VERSION 3.0)
project(std_adiog)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sandbox)
file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cc)
add_executable(std_adiog_test ${TEST_FILES})
target_link_libraries(std_adiog_test gtest pthread)
