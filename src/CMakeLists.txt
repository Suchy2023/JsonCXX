

add_library(
    src
    main.cpp
)

add_subdirectory(
    JsonParser
)

add_subdirectory(
    Core
)

add_executable(
    main
    main.cpp
)

target_include_directories(
    main
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    main
    PRIVATE
    Core
    JsonParser
)
