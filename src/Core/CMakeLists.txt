
add_library(
    Core
    some.cpp
)

target_include_directories(
    Core
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)