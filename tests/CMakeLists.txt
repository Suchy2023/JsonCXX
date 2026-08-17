


find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

function(add_project_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/JsonC++)
    gtest_discover_tests(${TEST_NAME})
endfunction()

add_subdirectory(Core)