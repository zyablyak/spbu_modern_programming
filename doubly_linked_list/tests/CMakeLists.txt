set(SOURCES
    test_doubly_linked_list.cpp
    templates_list.cpp
)
add_executable(test_doubly_linked_list ${SOURCES})

target_link_libraries(test_doubly_linked_list
	gtest
        doubly_linked_list_lib
        ${CONTAINERS_LIB}
)

add_test(test_doubly_linked_list test_doubly_linked_list)
