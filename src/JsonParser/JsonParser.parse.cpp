
#include "JsonC++/Core/JsonValue.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "JsonC++/JsonParser/JsonParser.h"
#include <expected>

namespace JsonParser
{

    std::expected<Core::JsonValue, JsonParserError> JsonParser::parse(std::string_view value)
    {
       const auto iterator = value.begin();
       
       const auto end = value.end();
    }

}