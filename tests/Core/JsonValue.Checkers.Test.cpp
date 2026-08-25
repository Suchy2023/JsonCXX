
#include "JsonC++/Core/JsonValue.h"
#include "JsonC++/Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <string>

namespace Tests {

template <typename T> class JsonValue_Checkers_Test : public ::testing::Test {};

using JsonUnderlyingTypes =
    ::testing::Types<Core::Json_Null, Core::Json_Int64, Core::Json_Double,
                     Core::Json_String, Core::Json_Object, Core::Json_Array>;

TYPED_TEST_SUITE(JsonValue_Checkers_Test, JsonUnderlyingTypes);

TYPED_TEST(JsonValue_Checkers_Test, is_returns_true_for_own_type) {
  using T = TypeParam;

  Core::JsonValue json{T{}};

  EXPECT_TRUE(json.is<T>());
}
} // namespace Tests

TEST(JsonValue_Checkers_Test, has_returns_true_when_key_exists) {

  Core::JsonValue json{};

  json.emplace("key", 1);

  EXPECT_TRUE(json.has("key"));
}

TEST(JsonValue_Checkers_Test, has_returns_false_when_key_not_found) {

  Core::JsonValue json{Core::Json_Object{}};

  const auto result = json.has("key");

  EXPECT_TRUE(result.has_value());

  EXPECT_FALSE(result.value());
}
