add_library(bigint_fuzzing SHARED "../private/bigint.c")
target_include_directories(bigint_fuzzing
  PUBLIC "../public"
  PRIVATE "../private")
