
#pragma once

#include "JsonC++/Core/JsonValue.h"
#include "JsonParserError.h"
#include "cmath"
#include <cctype>
#include <expected>
#include <string>
#include <string_view>

namespace JsonParser
{

struct ParseResult
{
    const char *iterator;
    Core::JsonValue json;
};

class JsonParser
{

  public:
    static std::expected<Core::JsonValue, JsonParserError> parse(std::string_view value);

    static Core::JsonValue parseNumber(const char *&iterator, const char *const &end);

    static std::expected<int, JsonParserError> parseInt(const char *&iterator, const char *const &end);

    static Core::JsonValue parseFloat(const char *&iterator, const char *const &end);

    static Core::JsonValue parseDouble(const char *&iterator, const char *const &end);

    static std::string parseString(const char *&iterator, const char *const &end);

    static Core::JsonValue parseObject(const char *&iterator, const char *const &end);

    static Core::JsonValue parseArray(const char *&iterator, const char *const end);

    static Core::JsonValue iterate(const char *&iterator, const char *const end);

    static Core::JsonValue getValue(const char *&iterator, const char *const &end);
};
} // namespace JsonParser