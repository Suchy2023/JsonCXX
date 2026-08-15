
#include "Core/JsonValue.h"
#include <gtest/gtest.h>
#include <string>

TEST(JsonValue_Test, is_works) {
  auto json = Core::JsonValue{};

  EXPECT_TRUE(json.isNull());
}

TEST(JsonValue_Test, defaults_to_null) {
  const auto jsonValue = Core::JsonValue{};

  EXPECT_TRUE(jsonValue.isNull()) << "Json isn't null";
};

TEST(JsonValue_Test, emplace_works) {

  auto jsonValue = Core::JsonValue{};
  auto nextJsonValue = Core::JsonValue{};

  constexpr auto fieldName = "";

  const auto result = jsonValue.emplace(fieldName, nextJsonValue);

  EXPECT_TRUE(result);
};

TEST(JsonValue_Test, emplace_places_has_bools) {
  auto json = Core::JsonValue{};
  auto nextJsonValue = Core::JsonValue{};

  const auto emplaceResult = json.emplace("wujek", nextJsonValue);

  const auto hasResult = json.has("wujek");

  EXPECT_TRUE(hasResult.has_value());

  EXPECT_TRUE(hasResult.value());
}

TEST(JsonValue_Test, get_works) {
  auto json = Core::JsonValue{};
  auto nextJsonValue = Core::JsonValue{};

  const auto emplaceResult = json.emplace("wujek", nextJsonValue);

  const auto getResult = json.get("wujek");

  EXPECT_TRUE(getResult.has_value());

  // TODO
  //  EXPECT_EQ(getResult.value(), nextJsonValue);
}

TEST(JsonValue_Test, equality_operator) {

  const auto json = Core::JsonValue{};

  json.strictlyEquals(1);
}
