

add_library(Core INTERFACE)

target_include_directories(
    Core
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
