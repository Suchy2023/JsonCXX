

add_library(
    JsonParser
    JsonParser.parseString.cpp
    JsonParser.parseNumber.cpp
    parseString.helpers.cpp
    parseNumber.helpers.cpp
    char.helpers.cpp
)

target_include_directories(
    JsonParser
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/JsonParser
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    JsonParser
    PRIVATE
    Core
)