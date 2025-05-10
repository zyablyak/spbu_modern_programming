set(SOURCES
    test_vector.cpp
    templates_vector.cpp
)
add_executable(test_vector ${SOURCES})

target_link_libraries(test_vector
	gtest
        vector_lib
        ${CONTAINERS_LIB}
)

add_test(test_vector test_vector)
