

add_library(
    JsonParser
    helpers.cpp
    JsonParser.getValue.cpp
    JsonParser.parse.cpp
    JsonParser.parseArray.cpp
    JsonParser.parseObject.cpp
    JsonParser.parseString.cpp
    JsonParser.iterate.cpp
    JsonParser.parseNumber.cpp
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