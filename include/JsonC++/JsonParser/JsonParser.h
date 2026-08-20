

#include "Core/JsonValue.Types.h"
#include "Core/JsonValue.h"
#include "JsonParserError.h"
#include "cmath"
#include <algorithm>
#include <cctype>
#include <expected>
#include <iostream>
#include <map>
#include <ostream>
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
  static std::expected<Core::JsonValue, JsonParserError>
  parse(std::string_view value)
  {
    auto iterator = value.begin();
    const char *const end = value.end();

    auto json = Core::JsonValue{};

    while (iterator != end)
    {
      const bool isDigit = std::isdigit(*iterator);
      const bool isString = *iterator == 34;
      const bool isObject = *iterator == 123;
      const bool isArray = *iterator == 91;

      if (isDigit)
      {
        json = parseNumber(iterator, end);
      }
      else if (isString)
      {
        json = parseString(iterator, end);
      }
      else if (isObject)
      {
        json = parseObject(iterator, end);
      }
      else
      {
        iterator++;
      }
    };

    return json;
  };

private:
  static Core::JsonValue parseNumber(const char *&iterator,
                                     const char *const end)
  {
    double currentNumber{};
    int digitsAfterDot{};

    bool isFloating = false;
    bool prevDigit = false;
    bool isDigit = true;

    for (; iterator != end; ++iterator)
    {
      isDigit = std::isdigit(*iterator);

      if (*iterator == 46)
      {
        isDigit = false;
        isFloating = true;
      }

      if (isDigit)
      {

        if (isFloating)
        {
          digitsAfterDot++;
          const double toAdd =
              (double)(*iterator - 48) / std::pow(10, digitsAfterDot);
          currentNumber = (currentNumber + toAdd);
        }
        else if (prevDigit)
        {
          currentNumber = currentNumber * 10 + *iterator - 48;
        }
        else
        {
          prevDigit = true;
          currentNumber = currentNumber * 10 + *iterator - 48;
        }
      }
    };

    return Core::JsonValue{currentNumber};
  };

  static std::string parseString(const char *&iterator, const char *const end)
  {
    std::string result{};

    bool stringStarted = true;

    for (; iterator != end; ++iterator)
    {
      if (*iterator == 34)
      {
        stringStarted = true;
        continue;
      }

      result += *iterator;
    }

    return std::move(result);
  };

  static Core::JsonValue parseObject(const char *&iterator,
                                     const char *const end)
  {
    iterator++;
    bool keyStarted = false;
    std::string currentKey{};
    bool afterValueStatement = false;

    auto json = Core::JsonValue{Core::JsonObject{}};

    for (; iterator != end; ++iterator)
    {
      if (afterValueStatement)
      {
        if (std::isdigit(*iterator))
        {
          auto result = json.emplace(currentKey, parseNumber(iterator, end));
        }

        currentKey.clear();
        keyStarted = false;
        afterValueStatement = false;  
        continue;
      }

      if (*iterator == 58)
      {
        afterValueStatement = true;
        continue;
      }
      if (*iterator == 34 && keyStarted)
      {
        keyStarted = false;
      }
      else if (keyStarted)
      {
        currentKey += *iterator;
      }
      else if (*iterator == 34)
      {
        keyStarted = true;
        continue;
      }
    }

    return json;
  };

  std::expected<void, JsonParserError> parseArray() {

  };
};

} // namespace JsonParser