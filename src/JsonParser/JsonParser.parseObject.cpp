
#include "JsonC++/Core/JsonValue.h"
#include "JsonC++/JsonParser/JsonParser.h"
#include "helpers.h"
#include <iostream>

namespace JsonParser
{
    Core::JsonValue JsonParser::parseObject(const char *&iterator,
                                     const char *const &end) {
    std::cout << "parsing_object" << std::endl;

    iterator++;
    std::string currentKey{};
    bool afterColon = false;

    auto json = Core::JsonValue{Core::JsonObject{}};

    for (; iterator != end; ++iterator) {

      if (*iterator == 125) {
        return json;
      }

      if (afterColon) {

        std::cout << "after stat" << std::endl;

        const auto result = json.emplace(currentKey, iterate(iterator, end));
        std::cout << "emplace result: " << result.has_value() << std::endl;

        currentKey.clear();
        afterColon = false;
        continue;
      }

      if (Helpers::isDoubleQuote(iterator)) {
        currentKey = parseString(iterator, end);
        continue;
      }

      if (Helpers::isColon(iterator)) {
        std::cout << "colon" << std::endl;
        afterColon = true;
        continue;
      }
    }

    return json;
  };
}