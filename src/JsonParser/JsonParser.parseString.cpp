#include "JsonC++/JsonParser/JsonParser.h"

namespace JsonParser {
std::string JsonParser::parseString(const char *&iterator, const char *const &end) {

  std::string result{};

  bool stringStarted = true;

  for (; iterator != end; ++iterator) {
    if (*iterator == 34) {
      stringStarted = true;
      continue;
    }

    result += *iterator;
  }

  return std::move(result);
};
} // namespace JsonParser