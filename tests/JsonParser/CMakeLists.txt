

add_project_test(
    JsonParser_Tests
    char.helpers.Test.cpp
    JsonParser.parseNumber.Test.cpp
    parseString.helpers.Test.cpp
)

target_include_directories(
    JsonParser_Tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/JsonParser
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/helpers
   
)

target_link_libraries(
    JsonParser_Tests
    PRIVATE
    JsonParser
    Core
)