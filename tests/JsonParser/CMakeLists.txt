

add_project_test(
    JsonParser_Tests
    JsonParser.Test.cpp
    helpers.Test.cpp
)

target_include_directories(
    JsonParser_Tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/JsonParser
    ${CMAKE_SOURCE_DIR}/include
   
)

target_link_libraries(
    JsonParser_Tests
    PRIVATE
    JsonParser
    Core
)