

add_library(
    src
    main.cpp
)

target_include_directories(
    src
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/JsonC++
)

add_executable(
    json_cpp_main
    main.cpp
)

target_include_directories(
    json_cpp_main
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/JsonC++
)
