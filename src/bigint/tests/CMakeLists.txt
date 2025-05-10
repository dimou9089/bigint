add_executable(tests_bigint_add "main_add.c")
add_executable(tests_bigint_mul "main_mul.c")

target_link_libraries(tests_bigint_add bigint)
target_link_libraries(tests_bigint_add unity)

target_link_libraries(tests_bigint_mul bigint)
target_link_libraries(tests_bigint_mul unity)
