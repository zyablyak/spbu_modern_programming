cmake_minimum_required(VERSION 3.2...3.27.5)

project(cmake_prog)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(bubble_sort)
add_subdirectory(obuchaika)
add_subdirectory(unit_test_example)
add_subdirectory(long_numbers)
add_subdirectory(vector)
add_subdirectory(doubly_linked_list)




set(CMAKE_SUPPRES_REGENERATION true)
