add_library(bigint "private/bigint.c")
target_include_directories(bigint
  PUBLIC public
  PRIVATE private)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
if (BUILD_FUZZING)
  add_subdirectory(fuzzing)
endif()
