set(SOURCES
    test_long_numbers.cpp
)
add_executable(test_long_numbers ${SOURCES})
target_link_libraries(test_long_numbers
    gtest_main
    long_numbers_lib
)

add_test(test_long_numbers test_long_numbers)
