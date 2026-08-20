

#include "JsonParser/JsonParser.h"
#include <gtest/gtest.h>
#include <string>

TEST(JsonParserTest, number)
{
  const char *intJson = R"(125.75)";

  const auto result = JsonParser::JsonParser::parse(intJson);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result->is<double>());

  EXPECT_TRUE(result->as<double>() == 125.75);
}

TEST(JsonParserTest, string)
{
  const char *stringJson = R"("1")";

  const auto result = JsonParser::JsonParser::parse(stringJson);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result->is<std::string>());

  EXPECT_TRUE(result->as<std::string>()->get() == "1");
}

TEST(JsonParserTest, object)
{
  const char *objectJson = R"({"key": 1})";

  const auto result = JsonParser::JsonParser::parse(objectJson);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result->isObject());

  EXPECT_TRUE(result->has("key"));
}