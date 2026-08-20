
#include "JsonParser/JsonParser.h"
#include <string_view>

int main()
{
  const auto toParse = R"({"key": 1})";

  const auto result = JsonParser::JsonParser::parse(toParse);

};