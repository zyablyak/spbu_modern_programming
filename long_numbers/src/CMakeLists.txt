target_sources(long_numbers_lib
    PRIVATE
        main.cpp
    PUBLIC
        main.hpp
)
target_include_directories(long_numbers_lib PUBLIC
         "${PROJECT_SOURCE_DIR}/src"


)
