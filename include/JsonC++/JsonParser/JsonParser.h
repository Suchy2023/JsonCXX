
#pragma once

#include "JsonC++/Core/JsonValue.Types.h"
#include "JsonC++/Core/JsonValue.h"
#include "JsonParser.Concepts.h"
#include "JsonParserError.h"
#include "cmath"
#include <cctype>
#include <expected>
#include <string>
#include <string_view>
#include <variant>

namespace JsonParser
{

class JsonParser
{

    using Iterator = const char *&;
    using End = const char *const &;

  public:
    static std::expected<Core::JsonValue, JsonParserError> parse(std::string_view value);

    static std::expected<std::variant<Core::Json_Int64, Core::Json_UInt64, Core::Json_Double>, JsonParserError> parseNumber(Iterator iterator, End end);

    static std::string parseString(Iterator iterator, End end);

    static Core::JsonValue parseObject(Iterator iterator, End end);

    static Core::JsonValue parseArray(Iterator iterator, End end);

    static Core::JsonValue iterate(Iterator iterator, End end);

    static Core::JsonValue getValue(Iterator iterator, End end);

    struct CountDigitsResult
    {
        unsigned short digitsCount;
        unsigned short floatingDigitsCount;
    };

    static std::expected<CountDigitsResult, JsonParserError> countDigits(const char* iterator, End end);
};
} // namespace JsonParser