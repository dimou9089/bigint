project(bigint)
cmake_minimum_required(VERSION 3.25)
set(CMAKE_BUILD_TYPE Debug)
option(BUILD_FUZZING "Compiler les targets pour fuzzing" ON)
add_subdirectory(main)
add_subdirectory(bigint)
if (BUILD_TESTS)
  add_subdirectory(unity)
endif()
