project(long_numbers)

add_library(long_numbers_lib)
add_subdirectory(src)
add_subdirectory(tests)

set(CMAKE_SUPPRESS_REGENERATION true)
