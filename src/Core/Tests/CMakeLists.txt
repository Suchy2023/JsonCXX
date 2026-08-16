
add_executable(
    CoreTests
    JsonValue_Test.cpp
    JsonValue.Accessors.Test.cpp
    JsonValue.Constructors.Test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(
    CoreTests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

target_include_directories(
    CoreTests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/JsonC++
)

include(GoogleTest)
gtest_discover_tests(
    CoreTests
    PROPERTIES
    LABELS
    "unit"
    )