
#pragma once

#include "JsonC++/Core/JsonValue.h"
#include "JsonParser.Concepts.h"
#include "JsonParserError.h"
#include "cmath"
#include <cctype>
#include <expected>
#include <string>
#include <string_view>

namespace JsonParser
{

class JsonParser
{

    using Iterator = const char *&;
    using End = const char *const &;

  public:
    static std::expected<Core::JsonValue, JsonParserError> parse(std::string_view value);

    static Core::JsonValue parseNumber(Iterator iterator, End end);

    template <Integral T> static std::expected<T, JsonParserError> parseIntegral(Iterator iterator, End end);

    template <Floating T> static std::expected<T, JsonParserError> parseFloating(Iterator iterator, End end);

    static std::string parseString(Iterator iterator, End end);

    static Core::JsonValue parseObject(Iterator iterator, End end);

    static Core::JsonValue parseArray(Iterator iterator, End end);

    static Core::JsonValue iterate(Iterator iterator, End end);

    static Core::JsonValue getValue(Iterator iterator, End end);
};
} // namespace JsonParser

#include "JsonParser.parseIntegral.tpp"