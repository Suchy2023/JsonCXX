
#include "JsonC++/JsonParser/JsonParser.h"
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

TEST(JsonParserTest, number) {
  const char *intJson = R"(125.75)";

  const auto result = JsonParser::JsonParser::parse(intJson);

  ASSERT_FALSE(std::is_void_v<decltype(result)>);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result->is<double>());

  EXPECT_TRUE(result->as<double>() == 125.75);
}

TEST(JsonParserTest, string) {
  const char *stringJson = R"("1")";

  const auto result = JsonParser::JsonParser::parse(stringJson);

  ASSERT_FALSE(std::is_void_v<decltype(result)>);

  ASSERT_TRUE(result.has_value());

  EXPECT_TRUE(result.value().is<std::string>());

  EXPECT_TRUE(result.value().as<std::string>()->get() == "1");
}

TEST(JsonParserTest, object) {
  const char *objectJson = R"({"key": 1})";

  const auto result = JsonParser::JsonParser::parse(objectJson);

  ASSERT_FALSE(std::is_void_v<decltype(result)>);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result->isObject());

  EXPECT_TRUE(result->has("key"));
}

TEST(JsonParserTest, nested_object) {
  const char *objectJson = R"({"key": {"nested_key": 1}})";

  const auto result = JsonParser::JsonParser::parse(objectJson);

  ASSERT_FALSE(std::is_void_v<decltype(result)>);

  EXPECT_TRUE(result.has_value());

  EXPECT_TRUE(result.value().isObject());

  EXPECT_TRUE(result.value().has("key"));

  const auto nested = result.value().get("key");

  EXPECT_TRUE(nested.has_value());

  const auto nestedValue = nested.value();

  EXPECT_TRUE(nestedValue.isObject());

  EXPECT_TRUE(nestedValue.has("nested_key"));

  const auto nestedInt = nestedValue.get("nested_key");

  EXPECT_TRUE(nestedInt.has_value());

  const auto nestedIntValue = nestedInt.value();

  EXPECT_TRUE(nestedIntValue.is<double>());

  EXPECT_TRUE(nestedIntValue.as<double>().value().get() == 1.0);
}
