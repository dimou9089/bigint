add_executable(tests_bigint_add "main_add.c")
add_executable(tests_bigint_sub "main_sub.c")
add_executable(tests_bigint_mul "main_mul.c")
add_executable(tests_bigint_cmp "main_cmp.c")
add_executable(tests_bigint_mod "main_mod.c")
add_executable(tests_bigint_private "main_private.c")

target_link_libraries(tests_bigint_add bigint)
target_link_libraries(tests_bigint_add unity)

target_link_libraries(tests_bigint_sub bigint)
target_link_libraries(tests_bigint_sub unity)

target_link_libraries(tests_bigint_mul bigint)
target_link_libraries(tests_bigint_mul unity)

target_link_libraries(tests_bigint_cmp bigint)
target_link_libraries(tests_bigint_cmp unity)

target_link_libraries(tests_bigint_mod bigint)
target_link_libraries(tests_bigint_mod unity)

target_link_libraries(tests_bigint_private bigint)
target_link_libraries(tests_bigint_private unity)
