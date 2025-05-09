cmake_minimum_required(VERSION 3.2...3.27.5)

project(cmake_prog)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(bubble_sort)
add_subdirectory(obuchaika)
add_subdirectory(unit_test_example)
add_subdirectory(long_numbers)
#add_subdirectory(scl_homework)
#add_subdirectory(long_number)
#add_subdirectory(long_numbers_2)



set(CMAKE_SUPPRES_REGENERATION true)
